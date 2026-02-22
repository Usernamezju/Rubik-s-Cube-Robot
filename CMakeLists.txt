cmake_minimum_required(VERSION 3.12)
project(cube_robot)

# --- 核心修改：针对 Windows 用户 ---
# 如果你是 Windows，取消下面这行的注释并修改为你解压的实际路径
# set(OpenCV_DIR "D:/opencv/build") 


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(OpenCV REQUIRED)

# 告诉 pybind11 我们的模块名
find_package(pybind11 REQUIRED)

# 确保把所有新创建的 .cpp 文件都加进来，否则会报“未定义的引用”
pybind11_add_module(cube_engine 
    binding.cpp 
    RGB_to_HSV.cpp 
    serial.cpp 
    process_image.cpp 
    Grid_Detector.cpp 
    instruction_parser.cpp
)

target_link_libraries(cube_engine PRIVATE ${OpenCV_LIBS})