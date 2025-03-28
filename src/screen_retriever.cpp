#include "screen_retriever.h"

// Forward declarations for platform-specific implementations
#ifdef __APPLE__
#include "screen_retriever_macos.h"
#elif defined(_WIN32)
#include "screen_retriever_windows.h"
#else
#include "screen_retriever_linux.h"
#endif

namespace nativeapi {

std::unique_ptr<ScreenRetriever> ScreenRetriever::instance_ = nullptr;

ScreenRetriever& ScreenRetriever::GetInstance() {
  if (!instance_) {
#ifdef __APPLE__
    instance_ = std::unique_ptr<ScreenRetriever>(new ScreenRetrieverMacOS());
#elif defined(_WIN32)
    instance_ = std::unique_ptr<ScreenRetriever>(new ScreenRetrieverWindows());
#else
    instance_ = std::unique_ptr<ScreenRetriever>(new ScreenRetrieverLinux());
#endif
  }
  return *instance_;
}

}  // namespace nativeapi