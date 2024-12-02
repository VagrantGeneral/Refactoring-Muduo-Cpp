cmake_minimum_required(VERSION 3.0)
project(mymuduo)

# 设置输出路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 设置so动态库的输出路径
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

# 设置调试信息 以及 C++11语言标准
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11 -fPIC")

# 参与编译的源文件路径
aux_source_directory(. SRC_FILE)

# 编译生成so动态库
add_library(mymuduo SHARED ${SRC_FILE})

# 编译生成可执行文件
add_executable(test ${SRC_FILE}) 