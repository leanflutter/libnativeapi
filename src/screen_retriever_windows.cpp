#include "screen_retriever_windows.h"
#include <iostream>

namespace nativeapi {

ScreenRetrieverWindows::ScreenRetrieverWindows() {
  // Constructor implementation
  std::cout << "ScreenRetrieverWindows initialized" << std::endl;
}

ScreenRetrieverWindows::~ScreenRetrieverWindows() {
  // Destructor implementation
  std::cout << "ScreenRetrieverWindows destroyed" << std::endl;
}

Point ScreenRetrieverWindows::GetCursorScreenPoint() {
  // Empty implementation
  Point point;
  point.x = 0.0;
  point.y = 0.0;
  return point;
}

Display ScreenRetrieverWindows::GetPrimaryDisplay() {
  // Empty implementation
  Display display;
  display.id = "display-1";
  display.name = "Windows Display";
  display.width = 1920.0;
  display.height = 1080.0;
  display.visiblePositionX = 0.0;
  display.visiblePositionY = 0.0;
  display.visibleSizeWidth = 1920.0;
  display.visibleSizeHeight = 1080.0;
  display.scaleFactor = 1.0;
  return display;
}

std::vector<Display> ScreenRetrieverWindows::GetAllDisplays() {
  // Empty implementation
  std::vector<Display> displayList;
  displayList.push_back(GetPrimaryDisplay());
  return displayList;
}

}  // namespace nativeapi
