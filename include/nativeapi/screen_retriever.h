#pragma once

#include <functional>
#include <memory>
#include <vector>

#include "ui/display.h"
#include "ui/geometry.h"

namespace nativeapi {

// Event types that can be listened to
enum ScreenEventType {
  kDisplayAdded,    // New display connected
  kDisplayRemoved,  // Display disconnected
};

// Abstract base class for ScreenRetriever
class ScreenRetriever {
 public:
  virtual ~ScreenRetriever() = default;

  // Delete copy constructor and assignment operator
  ScreenRetriever(const ScreenRetriever&) = delete;
  ScreenRetriever& operator=(const ScreenRetriever&) = delete;

  // Get singleton instance
  static ScreenRetriever& GetInstance();

  // Get the current cursor screen point
  virtual Point GetCursorScreenPoint() = 0;

  // Get the primary display information
  virtual Display GetPrimaryDisplay() = 0;

  // Get all displays information
  virtual std::vector<Display> GetAllDisplays() = 0;

  // Add event listener for specific event type
  virtual void AddEventListener(ScreenEventType event_type,
                                std::function<void(const void*)> listener) = 0;

  // Remove event listener for specific event type
  virtual void RemoveEventListener(
      ScreenEventType event_type,
      std::function<void(const void*)> listener) = 0;

 protected:
  // Protected constructor for singleton
  ScreenRetriever() = default;

 private:
  // Static instance holder
  static std::unique_ptr<ScreenRetriever> instance_;
};

}  // namespace nativeapi 