file(GLOB_RECURSE SRC_FILES src/*.cc)
file(GLOB_RECURSE HEADER_FILES include/*.h)

add_library(core ${SRC_FILES} ${HEADER_FILES})

target_include_directories(core PUBLIC include/)

if (MSVC)
target_compile_options(core PUBLIC /WX)
endif (MSVC)

if(ENABLE_TESTING)
    file(GLOB_RECURSE TEST_FILES test/*.cc)
    add_executable(core_test ${TEST_FILES})
    target_link_libraries(core_test PRIVATE GTest::gtest GTest::gtest_main core)
endif(ENABLE_TESTING)

if(ENABLE_PROFILING)
    target_link_libraries(core PRIVATE Tracy::TracyClient)
    target_compile_definitions(core PUBLIC TRACY_ENABLE)
endif(ENABLE_PROFILING)
