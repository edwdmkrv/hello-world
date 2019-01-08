cmake_minimum_required (VERSION 3.2)

set (TRAVIS_BUILD_NUMBER "$ENV{TRAVIS_BUILD_NUMBER}")

if ("${TRAVIS_BUILD_NUMBER}" STREQUAL "")
	set (TRAVIS_BUILD_NUMBER "1")
endif ("${TRAVIS_BUILD_NUMBER}" STREQUAL "")

project (helloworld VERSION 0.0.${TRAVIS_BUILD_NUMBER})

find_package (GTest REQUIRED)
find_package (Threads REQUIRED)

configure_file (version.h.in ${CMAKE_SOURCE_DIR}/version.h)

add_executable (helloworld_cli main.cpp)

add_library (helloworld lib.cpp)

add_executable (test_version test_version.cpp)

set_target_properties (helloworld_cli helloworld test_version PROPERTIES
	CXX_STANDARD 17
	CXX_EXTENSIONS OFF
	CXX_STANDARD_REQUIRED ON
	COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)

target_link_libraries (helloworld_cli
	PRIVATE helloworld
	PRIVATE "${CMAKE_THREAD_LIBS_INIT}"
)

target_include_directories (test_version
	PRIVATE "${GTEST_INCLUDE_DIR}"
)

target_link_libraries (test_version
	PRIVATE "${GTEST_LIBRARY}"
	PRIVATE "${GTEST_MAIN_LIBRARY}"
	PRIVATE "${CMAKE_THREAD_LIBS_INIT}"
	PRIVATE helloworld
)

install (TARGETS helloworld_cli RUNTIME DESTINATION bin)

set (CPACK_GENERATOR DEB)

set (CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set (CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set (CPACK_PACKAGE_CONTACT myname@company.com)

include (CPack)

enable_testing ()

add_test (test_version test_version)
