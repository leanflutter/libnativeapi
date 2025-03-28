#pragma once

#include "screen_retriever.h"

namespace nativeapi {

// Windows implementation of ScreenRetriever
class ScreenRetrieverWindows : public ScreenRetriever {
 public:
  ScreenRetrieverWindows();
  ~ScreenRetrieverWindows() override;

  nativeapi::Point GetCursorScreenPoint() override;
  Display GetPrimaryDisplay() override;
  std::vector<Display> GetAllDisplays() override;
};

}  // namespace nativeapi
