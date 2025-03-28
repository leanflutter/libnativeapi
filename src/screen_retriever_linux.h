#pragma once

#include "screen_retriever.h"

namespace nativeapi {

// Linux implementation of ScreenRetriever
class ScreenRetrieverLinux : public ScreenRetriever {
 public:
  ScreenRetrieverLinux();
  ~ScreenRetrieverLinux() override;

  Point GetCursorScreenPoint() override;
  Display GetPrimaryDisplay() override;
  std::vector<Display> GetAllDisplays() override;
};

}  // namespace nativeapi
