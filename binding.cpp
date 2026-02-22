#include <pybind11/pybind11.h>
#include <pybind11/stl.h> // 极其重要：有了它，std::vector 会自动变成 Python 的 list
#include "cube_vision.h"
#include <pybind11/numpy.h>
namespace py = pybind11;

PYBIND11_MODULE(cube_engine, m) {
    m.doc() = "浙大魔方机器人加速引擎";

    // 1. 导出 HSV 结构体
    py::class_<HSV>(m, "HSV")
        .def_readwrite("h", &HSV::h)
        .def_readwrite("s", &HSV::s)
        .def_readwrite("v", &HSV::v);

    // 2. 导出 Point2D 结构体 (新增)
    py::class_<Point2D>(m, "Point2D")
        .def_readwrite("x", &Point2D::x)
        .def_readwrite("y", &Point2D::y);

    // 3. 导出 Move 结构体 (新增)
    py::class_<Move>(m, "Move")
        .def_readwrite("face", &Move::face)
        .def_readwrite("degrees", &Move::degrees);

    // 4. 导出计算坐标函数 (新增)
    m.def("calculate_grid_points", &calculateGridPoints);

    // 5. 导出平均 HSV 计算函数 (新增)
    m.def("get_average_hsv", &getAverageHSV);

    // 6. 导出解法字符串解析函数 (新增)
    m.def("parse_solution", &parseSolution);


    // 8. 导出串口类
    py::class_<RobotSerial>(m, "RobotSerial")
        .def(py::init<>())
        .def("send_move", &RobotSerial::sendMove);
}