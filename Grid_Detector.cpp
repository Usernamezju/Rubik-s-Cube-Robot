
#include "cube_vision.h"

// 定义一个简单的结构存储坐标

std::vector<Point2D> calculateGridPoints(int frameWidth, int frameHeight, int step) {
    std::vector<Point2D> points;

    // 计算屏幕中心坐标
    int centerX = frameWidth / 2;
    int centerY = frameHeight / 2;

    // 使用双重循环生成 -1, 0, 1 的组合
    for (int row = -1; row <= 1; ++row) {
        for (int col = -1; col <= 1; ++col) {
            Point2D p;
            
            // --- 填空 1: 计算 X 坐标 ---
            // 提示：中心点坐标加上 (列索引 * 步长)
            p.x = centerX+step*col;

            // --- 填空 2: 计算 Y 坐标 ---
            // 提示：中心点坐标加上 (行索引 * 步长)
            p.y = centerY +step*row;

            points.push_back(p);
        }
    }
    return points;
}


HSV getAverageHSV(const cv::Mat& hsvMat, int centerX, int centerY, int radius) {
    float sumH = 0, sumS = 0, sumV = 0;
    int count = 0;

    // 遍历以 (centerX, centerY) 为中心，radius 为半径的方块
    for (int y = centerY - radius; y <= centerY + radius; ++y) {
        for (int x = centerX - radius; x <= centerX + radius; ++x) {
            // 安全检查：防止坐标越界
            if (x >= 0 && x < hsvMat.cols && y >= 0 && y < hsvMat.rows) {
                // --- 填空 3: 获取当前像素的 HSV ---
                // 提示：我们在上一节已经学会了用 .at 或指针获取自定义结构。
                // 假设我们这里有一个已经转好 HSV 的 Mat 对象
                HSV current = hsvMat.at<HSV>(y, x); 
                
                sumH += current.h;
                sumS += current.s;
                sumV += current.v;
                count++;
            }
        }
    }

    return {sumH / count, sumS / count, sumV / count};
}