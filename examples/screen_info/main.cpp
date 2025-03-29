#include <iostream>
#include <thread>
#include <chrono>
#include "libnativeapi.h"

using nativeapi::ScreenRetriever;
using nativeapi::Display;
using nativeapi::Point;
using nativeapi::ScreenEventType;

int main() {
  ScreenRetriever& screenRetriever = ScreenRetriever::GetInstance();

  // Set up event listeners
  screenRetriever.AddEventListener(ScreenEventType::kDisplayAdded,
      [](const void* data) {
          const auto* display = static_cast<const Display*>(data);
          std::cout << "\nNew display connected!" << std::endl;
          std::cout << "Display: " << display->name 
                    << " (" << display->width << "x" << display->height << ")" 
                    << std::endl;
          std::cout << "Position: (" << display->visiblePositionX 
                    << ", " << display->visiblePositionY << ")" << std::endl;
      });

  screenRetriever.AddEventListener(ScreenEventType::kDisplayRemoved,
      [](const void* data) {
          const auto* display = static_cast<const Display*>(data);
          std::cout << "\nDisplay disconnected!" << std::endl;
          std::cout << "Display: " << display->name << std::endl;
      });

  // Get primary display information
  Display primaryDisplay = screenRetriever.GetPrimaryDisplay();
  std::cout << "Primary Display Information:" << std::endl;
  std::cout << "ID: " << primaryDisplay.id << std::endl;
  std::cout << "Name: " << primaryDisplay.name << std::endl;
  std::cout << "Resolution: " << primaryDisplay.width << "x"
            << primaryDisplay.height << std::endl;
  std::cout << "Scale Factor: " << primaryDisplay.scaleFactor << std::endl;
  std::cout << "Visible Position: (" << primaryDisplay.visiblePositionX << ", "
            << primaryDisplay.visiblePositionY << ")" << std::endl;
  std::cout << "Visible Size: " << primaryDisplay.visibleSizeWidth << "x"
            << primaryDisplay.visibleSizeHeight << std::endl;
  std::cout << std::endl;

  // Get all displays information
  std::vector<Display> allDisplays = screenRetriever.GetAllDisplays();
  std::cout << "All Displays Information:" << std::endl;
  for (int i = 0; i < allDisplays.size(); i++) {
    Display& display = allDisplays[i];
    std::cout << "Display " << (i + 1) << ":" << std::endl;
    std::cout << "ID: " << display.id << std::endl;
    std::cout << "Name: " << display.name << std::endl;
    std::cout << "Resolution: " << display.width << "x" << display.height
              << std::endl;
    std::cout << "Scale Factor: " << display.scaleFactor << std::endl;
    std::cout << "Visible Position: (" << display.visiblePositionX << ", "
              << display.visiblePositionY << ")" << std::endl;
    std::cout << "Visible Size: " << display.visibleSizeWidth << "x"
              << display.visibleSizeHeight << std::endl;
    std::cout << std::endl;
  }

  // Get cursor position
  Point cursorPoint = screenRetriever.GetCursorScreenPoint();
  std::cout << "Current Cursor Position: (" << cursorPoint.x << ", "
            << cursorPoint.y << ")" << std::endl;

  // Keep the program running to observe display events
  std::cout << "\nMonitoring display events... (Press Ctrl+C to exit)" << std::endl;
  std::cout << "Try connecting or disconnecting a display..." << std::endl;
  while (true) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }

  return 0;
}