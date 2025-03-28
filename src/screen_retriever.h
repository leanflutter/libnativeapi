#pragma once

#include <memory>
#include <vector>

#include "ui/display.h"
#include "ui/geometry.h"

namespace nativeapi {
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

 protected:
  // Protected constructor for singleton
  ScreenRetriever() = default;

 private:
  // Static instance holder
  static std::unique_ptr<ScreenRetriever> instance_;
};

}  // namespace nativeapi