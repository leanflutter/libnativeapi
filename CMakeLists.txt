cmake_minimum_required(VERSION 3.10)

project(libnativeapi_library VERSION 0.0.1 LANGUAGES CXX)

# Add library subdirectory
add_subdirectory(src)

# Add example programs subdirectory
add_subdirectory(examples/display_example)
add_subdirectory(examples/nswindow_example)
add_subdirectory(examples/window_example)
