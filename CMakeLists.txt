cmake_minimum_required (VERSION 2.8)
project (checksum CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(GCC_COVERAGE_COMPILE_FLAGS "-std=c++11 -g ")

add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})
find_package(Qt4 REQUIRED QtGui QtWebKit QtTest)

add_executable(main checksum.cpp parent_window.cpp 
				checksum_window.cpp file_holder.cpp 
				checksum_data.cpp md5.cpp)
TARGET_LINK_LIBRARIES(main Qt4::QtGui Qt4::QtWebKit Qt4::QtTest)
