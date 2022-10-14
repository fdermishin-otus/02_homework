cmake_minimum_required(VERSION 3.23)
project(ip_filter)

add_executable(${PROJECT_NAME} src/main.cpp src/split.cpp)
target_compile_options(${PROJECT_NAME} PUBLIC -O3)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
target_include_directories(${PROJECT_NAME} PRIVATE include)

include(CTest)

if (BUILD_TESTING)
    include(FetchContent)
    FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG release-1.12.1
    )
    FetchContent_MakeAvailable(googletest)

    add_executable(${PROJECT_NAME}_test test/ipaddress_test.cpp test/split_test.cpp src/split.cpp)
    target_compile_features(${PROJECT_NAME}_test PUBLIC cxx_std_17)
    target_link_libraries(${PROJECT_NAME}_test GTest::gtest_main)
    target_include_directories(${PROJECT_NAME}_test PRIVATE include)

    include(GoogleTest)
    gtest_discover_tests(${PROJECT_NAME}_test)
endif ()

install(
        TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION bin
)

if (APPLE)
    message("Packing DragNDrop for MacOS")
    set(CPACK_GENERATOR DragNDrop)
elseif (UNIX)
    message("Packing DEB")
    set(CPACK_GENERATOR DEB)
    set(CPACK_PACKAGE_CONTACT fdermishin-otus@users.noreply.github.com)
endif ()
set(CPACK_OUTPUT_FILE_PREFIX release)
include(CPack)
