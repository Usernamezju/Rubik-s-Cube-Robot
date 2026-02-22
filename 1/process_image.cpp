#include "cube_vision.h"

void processImageHSV(const cv::Mat& input, cv::Mat& outputHue) {
    // 确保输出图像是单通道灰度图，大小与原图一致
    outputHue.create(input.size(), CV_8UC1);

    for (int y = 0; y < input.rows; ++y) {
        // --- 填空 1: 获取指针 ---
        // 提示：获取输入图像第 y 行的起始地址。BGR 图像每个像素 3 字节。
        const uint8_t* rowPtr = input.ptr<uint8_t>(y);
        
        // 获取输出图像第 y 行的起始地址
        uint8_t* outPtr = outputHue.ptr<uint8_t>(y);

        for (int x = 0; x < input.cols; ++x) {
            // --- 填空 2: 提取 BGR 分量 ---
            // 提示：OpenCV 默认是 BGR 顺序。rowPtr[0] 是 B，rowPtr[1] 是 G...
            uint8_t b = rowPtr[x * 3 + 0];
            uint8_t g = rowPtr[x * 3 + 1];
            uint8_t r = rowPtr[x*3+2]; 

            // 调用我们之前写的转换内核
            HSV hsv = manualRGBtoHSV(r, g, b);

            // --- 填空 3: 映射显示 ---
            // 提示：H 的范围是 0-360，但 uint8_t 只能存 0-255。
            // 我们需要做一个线性比例缩放。
            outPtr[x] = static_cast<uint8_t>(hsv.h * 255.0f / 360.0f);
        }
    }
}