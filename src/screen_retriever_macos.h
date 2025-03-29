#pragma once

#include <map>
#include "nativeapi/screen_retriever.h"

// Import Cocoa headers
#import <Cocoa/Cocoa.h>

namespace nativeapi {

// macOS implementation of ScreenRetriever
class ScreenRetrieverMacOS : public ScreenRetriever {
 public:
  ScreenRetrieverMacOS();
  ~ScreenRetrieverMacOS() override;

  Point GetCursorScreenPoint() override;
  Display GetPrimaryDisplay() override;
  std::vector<Display> GetAllDisplays() override;
  void AddEventListener(ScreenEventType event_type,
                        std::function<void(const void*)> listener) override;
  void RemoveEventListener(ScreenEventType event_type,
                           std::function<void(const void*)> listener) override;

 private:
  // Helper method to create Display struct from NSScreen
  Display CreateDisplayFromNSScreen(NSScreen* screen, bool isMainScreen);

  // Store current displays to detect changes
  std::vector<Display> current_displays_;

  // Event listeners storage
  std::map<ScreenEventType, std::vector<std::function<void(const void*)>>>
      listeners_;

  // Display observer handler
  id displayObserver_;

  // Helper method to detect display changes
  void HandleDisplayChange();
};

}  // namespace nativeapi
