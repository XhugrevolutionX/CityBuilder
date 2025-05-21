file(GLOB_RECURSE SRC_FILES src/*.cc)
file(GLOB_RECURSE HEADER_FILES include/*.h)

find_package(SFML COMPONENTS Graphics Window System Audio REQUIRED)

add_library(game ${SRC_FILES} ${HEADER_FILES})

target_include_directories(game PUBLIC include/)
target_link_libraries(game PUBLIC core SFML::Graphics SFML::Window SFML::Audio SFML::System)