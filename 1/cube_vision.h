#ifndef CUBE_VISION_H
#define CUBE_VISION_H

#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cstdint>
#include <opencv2/opencv.hpp>

// --- 1. 数据结构定义 ---
struct HSV {
    float h; // 0-360
    float s; // 0-1
    float v; // 0-1
};

// --- 2. 视觉算法声明 ---
// 提示：这里只写函数名和参数，不需要写具体的 {} 逻辑
// 这个函数负责单像素转换
HSV manualRGBtoHSV(uint8_t r, uint8_t g, uint8_t b);

// --- 3. 串口类定义 ---
class RobotSerial {
public:
    RobotSerial() { /* 构造函数 */ }
    
    // --- 填空 1: 声明成员函数 ---
    // 提示：还记得我们导出的那个发送指令的函数吗？
    void sendMove(char face, int angle_id);

private:
    // 底层发送逻辑，不导出给 Python，设为私有
    void sendRaw(const unsigned char* buffer, size_t length);
};

void processImageHSV(const cv::Mat& input, cv::Mat& outputHue);

struct Point2D {
    int x;
    int y;
};
std::vector<Point2D> calculateGridPoints(int frameWidth, int frameHeight, int step);
HSV getAverageHSV(const cv::Mat& hsvMat, int centerX, int centerY, int radius);
// 定义动作结构体
struct Move {
    char face;    // 哪一个面：'U', 'R', 'F', 'D', 'L', 'B'
    int degrees;  // 旋转角度：90, 180, -90
};
std::vector<Move> parseSolution(std::string solution);


#endif // CUBE_VISION_H