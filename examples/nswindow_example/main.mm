#include <AppKit/AppKit.h>
#import <Cocoa/Cocoa.h>
#include <iostream>
#include "nativeapi.h"

using nativeapi::Window;
using nativeapi::WindowManager;

@interface AppDelegate : NSObject <NSApplicationDelegate>
@property(strong) NSWindow* window;
@end

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification*)notification {
  // Create a window
  NSRect frame = NSMakeRect(0, 0, 400, 300);
  self.window = [[NSWindow alloc]
      initWithContentRect:frame
                styleMask:NSWindowStyleMaskTitled | NSWindowStyleMaskClosable |
                          NSWindowStyleMaskMiniaturizable | NSWindowStyleMaskResizable
                  backing:NSBackingStoreBuffered
                    defer:NO];
  [self.window setTitle:@"Native API Example"];
  [self.window center];
  [self.window makeKeyAndOrderFront:nil];
  [self.window makeMainWindow];
  [NSApp activateIgnoringOtherApps:YES];

  //   dispatch_async(dispatch_get_main_queue(), ^{

  //   });

  // 延迟检查主窗口
    dispatch_async(dispatch_get_main_queue(), ^{
        NSLog(@"主窗口: %@", NSApp.mainWindow);
        NSLog(@"关键窗口: %@", NSApp.keyWindow);
        NSLog(@"所有窗口: %@", NSApp.windows);
    });

  [[NSNotificationCenter defaultCenter]
      addObserverForName:NSWindowDidBecomeMainNotification
                  object:nil
                   queue:nil
              usingBlock:^(NSNotification* note) {
                NSWindow* mainWindow = [[NSApplication sharedApplication] mainWindow];
                NSLog(@"主窗口: %@", mainWindow);

                // Initialize WindowManager
                WindowManager windowManager = WindowManager();

                // Get current window information
                Window currentWindow = windowManager.GetCurrent();
                std::cout << "Current Window Information:" << std::endl;
                std::cout << "ID: " << currentWindow.id << std::endl;

               // Get window size
               auto size = currentWindow.GetSize();
               std::cout << "Window Size: " << size.width << "x" << size.height << std::endl;

               // Get all windows
               std::vector<Window> windowList = windowManager.GetAll();
               std::cout << "\nAll Windows Information:" << std::endl;
               for (size_t i = 0; i < windowList.size(); i++) {
                 const Window& window = windowList[i];
                 std::cout << "Window " << (i + 1) << ":" << std::endl;
                 std::cout << "ID: " << window.id << std::endl;
                 auto windowSize = window.GetSize();
                 std::cout << "Size: " << windowSize.width << "x" << windowSize.height
                           << std::endl;
               }
              }];
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication*)sender {
  return YES;
}

@end

int main(int argc, const char* argv[]) {
  @autoreleasepool {
    NSApplication* app = [NSApplication sharedApplication];
    AppDelegate* delegate = [[AppDelegate alloc] init];
    [app setDelegate:delegate];
    [app run];
  }
  return 0;
}