# Packages : external libraries managed by
find_package(SFML COMPONENTS Graphics Window System CONFIG REQUIRED)

file(GLOB_RECURSE SRC_FILES src/*.cc)
file(GLOB_RECURSE HEADER_FILES include/*.h)

add_library(api ${SRC_FILES} ${HEADER_FILES})

target_include_directories(api PUBLIC include/ PRIVATE D:/Work/SAE/vcpkg/installed/x86-windows/include)
target_link_libraries(api PUBLIC core SFML::System SFML::Graphics SFML::Window D:/Work/SAE/vcpkg/installed/x86-windows/lib/noise.lib)
