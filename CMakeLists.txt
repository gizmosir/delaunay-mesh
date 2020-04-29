cmake_minimum_required(VERSION 3.8)
project(delaunay-mesh)
set (CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(DESIRED_WARNINGS "-Wall -Wextra -Wconversion -Wunreachable-code -Wuninitialized -pedantic-errors -Wold-style-cast -Wno-error=unused-variable -Wshadow -Wfloat-equal -Weffc++")
if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  set(DESIRED_WARNINGS "${DESIRED_WARNINGS} -Wmost")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OPTIMIZATION_FLAGS} -D_GLIBCXX_USE_CXX11_ABI=0 ${DESIRED_WARNINGS}")

if (WERROR)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
endif()
find_package(Threads REQUIRED)

# 寻找OpenCV库
find_package(OpenCV 3.0 REQUIRED)
include_directories(${OPENCV_INCLUDE_DIR})

#设置本地OpenCV库
#file(GLOB OpenCV_LIBS "${PROJECT_SOURCE_DIR}/Thirdparty/opencv-3.3.1/lib/libopencv*.so")
#set(OPENCV_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/Thirdparty/opencv-3.3.1/include)

message(STATUS "${OpenCV_LIBS}")

# 添加源文件
include_directories("${PROJECT_SOURCE_DIR}/include")
aux_source_directory(src DIR_SRCS)


# executable
## project `delaunator-cpp`
add_executable(algor_1_test example/algor1.cpp ${DIR_SRCS})

### project `delaunay-triangulation`
add_executable(algor_2_test example/algor2.cpp ${DIR_SRCS})

## compare_test
add_executable(compare_test example/compare.cpp ${DIR_SRCS})

## illustrademo
add_executable(demo example/demo.cpp ${DIR_SRCS})
target_link_libraries(demo ${OpenCV_LIBS} )
