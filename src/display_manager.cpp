#include "display_manager.h"

namespace nativeapi {

void DisplayManager::AddListener(DisplayListener* listener) {
  listeners_.push_back(listener);
}

void DisplayManager::RemoveListener(DisplayListener* listener) {
  listeners_.erase(std::remove(listeners_.begin(), listeners_.end(), listener),
                   listeners_.end());
}

void DisplayManager::NotifyListeners(
    std::function<void(DisplayListener*)> callback) {
  for (const auto& listener : listeners_) {
    callback(listener);
  }
}

DisplayEventHandler::DisplayEventHandler(
    std::function<void(const Display&)> onDisplayAddedCallback,
    std::function<void(const Display&)> onDisplayRemovedCallback)
    : onDisplayAddedCallback_(onDisplayAddedCallback),
      onDisplayRemovedCallback_(onDisplayRemovedCallback) {}

void DisplayEventHandler::OnDisplayAdded(const Display& display) {
  if (onDisplayAddedCallback_) {
    onDisplayAddedCallback_(display);
  }
}

void DisplayEventHandler::OnDisplayRemoved(const Display& display) {
  if (onDisplayRemovedCallback_) {
    onDisplayRemovedCallback_(display);
  }
}

}  // namespace nativeapi
