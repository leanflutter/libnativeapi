#include "screen_retriever_macos.h"
#include <cstring>
#include <iostream>
#include <string>

// Import Cocoa headers
#import <Cocoa/Cocoa.h>

namespace nativeapi {

// Helper function to convert NSString to char*
static char* ConvertNSStringToCString(NSString* nsString) {
  if (nsString == nil) {
    return strdup("");
  }
  const char* cString = [nsString UTF8String];
  return cString ? strdup(cString) : strdup("");
}

ScreenRetrieverMacOS::ScreenRetrieverMacOS() {
  // Store initial display configuration
  current_displays_ = GetAllDisplays();

  // Set up display configuration change observer
  displayObserver_ = [[NSNotificationCenter defaultCenter]
      addObserverForName:NSApplicationDidChangeScreenParametersNotification
                  object:nil
                   queue:[NSOperationQueue mainQueue]
              usingBlock:^(NSNotification* notification) {
                HandleDisplayChange();
              }];
}

void ScreenRetrieverMacOS::HandleDisplayChange() {
  auto new_displays = GetAllDisplays();

  // Find added displays
  for (const auto& new_display : new_displays) {
    bool found = false;
    for (const auto& current_display : current_displays_) {
      if (new_display.id == current_display.id) {
        found = true;
        break;
      }
    }
    if (!found) {
      // This is a new display
      for (const auto& listener : listeners_[ScreenEventType::kDisplayAdded]) {
        listener(&new_display);
      }
    }
  }

  // Find removed displays
  for (const auto& current_display : current_displays_) {
    bool found = false;
    for (const auto& new_display : new_displays) {
      if (current_display.id == new_display.id) {
        found = true;
        break;
      }
    }
    if (!found) {
      // This display was removed
      for (const auto& listener : listeners_[ScreenEventType::kDisplayRemoved]) {
        listener(&current_display);
      }
    }
  }

  // Update current display list
  current_displays_ = std::move(new_displays);
}

ScreenRetrieverMacOS::~ScreenRetrieverMacOS() {
  // Remove observer
  if (displayObserver_) {
    [[NSNotificationCenter defaultCenter] removeObserver:displayObserver_];
  }
  // Note: cursor observer is automatically cleaned up when the run loop source is removed
}

Point ScreenRetrieverMacOS::GetCursorScreenPoint() {
  Point point;

  // Get the current mouse position
  NSPoint mouseLocation = [NSEvent mouseLocation];
  point.x = mouseLocation.x;
  point.y = mouseLocation.y;

  return point;
}

Display ScreenRetrieverMacOS::GetPrimaryDisplay() {
  // Get the primary display (first screen)
  NSArray<NSScreen*>* screens = [NSScreen screens];
  return CreateDisplayFromNSScreen(screens[0], true);
}

std::vector<Display> ScreenRetrieverMacOS::GetAllDisplays() {
  std::vector<Display> displayList;

  // Get all screens
  NSArray<NSScreen*>* screens = [NSScreen screens];
  bool isFirstScreen = true;
  for (NSScreen* screen in screens) {
    displayList.push_back(CreateDisplayFromNSScreen(screen, isFirstScreen));
    isFirstScreen = false;  // Only the first screen is the main screen
  }

  return displayList;
}

Display ScreenRetrieverMacOS::CreateDisplayFromNSScreen(NSScreen* screen, bool isFirstScreen) {
  Display display;

  // Get screen details
  NSRect frame = [screen frame];
  NSRect visibleFrame = [screen visibleFrame];
  CGFloat scaleFactor = [screen backingScaleFactor];

  // Set unique identifier for the screen using CGDirectDisplayID
  CGDirectDisplayID displayID =
      [[[screen deviceDescription] objectForKey:@"NSScreenNumber"] unsignedIntValue];
  NSString* screenId = [NSString stringWithFormat:@"%@", @(displayID)];
  display.id = ConvertNSStringToCString(screenId);

  // Set display name - use localizedName on macOS 10.15+
  NSString* displayName;
  if (@available(macOS 10.15, *)) {
    displayName = [screen localizedName];
  } else {
    displayName = isFirstScreen ? @"Primary Display"
                                : [NSString stringWithFormat:@"Display %@", @(displayID)];
  }
  display.name = ConvertNSStringToCString(displayName);

  // Set size and position properties
  display.width = frame.size.width;
  display.height = frame.size.height;
  display.visiblePositionX = visibleFrame.origin.x;
  display.visiblePositionY = visibleFrame.origin.y;
  display.visibleSizeWidth = visibleFrame.size.width;
  display.visibleSizeHeight = visibleFrame.size.height;
  display.scaleFactor = scaleFactor;

  return display;
}

void ScreenRetrieverMacOS::AddEventListener(ScreenEventType event_type,
                                            std::function<void(const void*)> listener) {
  listeners_[event_type].push_back(listener);
}

void ScreenRetrieverMacOS::RemoveEventListener(ScreenEventType event_type,
                                               std::function<void(const void*)> listener) {
  // Note: This is a simplified implementation that removes all listeners for the event type
  listeners_[event_type].clear();
}

}  // namespace nativeapi
