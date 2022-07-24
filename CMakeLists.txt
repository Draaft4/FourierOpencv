cmake_minimum_required(VERSION 3.0.0)
project(fourier VERSION 0.1.0)

include(CTest)
enable_testing()
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
include_directories("C:/fftw/")

add_executable(fourier main.cpp)

target_link_libraries( fourier ${OpenCV_LIBS} )

set_property(TARGET fourier PROPERTY CXX_STANDARD 17)  
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
