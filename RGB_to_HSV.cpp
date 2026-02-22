#include <iostream>
#include <algorithm> // 必须包含，用于 std::max 和 std::min
#include <cmath>     // 用于 fmod (取余)
#include "cube_vision.h"
// 定义一个结构体来存储结果



HSV manualRGBtoHSV(uint8_t r_int, uint8_t g_int, uint8_t b_int) {
    HSV out;
    
    // 归一化处理
    float r = r_int / 255.0f;
    float g = g_int / 255.0f;
    float b = b_int / 255.0f; 

    float cmax = std::max({r, g, b});
    float cmin = std::min({r, g, b});
    float delta = cmax - cmin;

    // --- 填空 1: 亮度 V ---
    // 提示：亮度 V 取决于三原色中最亮的那一个分量。
    out.v = cmax; 

    // --- 填空 2: 饱和度 S ---
    // 提示：如果 cmax 不为 0，S 等于 色彩差异(delta) 占 亮度(cmax) 的比例。
    if (cmax > 0.0f) {
        out.s = delta/out.v; 
    } else {
        out.s = 0.0f;
    }

    // --- 填空 3: 色相 H 的偏移逻辑 ---
    // 提示：当绿色主导(cmax == g)时，我们在色相环 120 度(即 2 * 60度)的基础上进行微调。
    // 请问公式括号内加上的偏移常数是多少？
    if (delta == 0.0f) {
        out.h = 0.0f;
    } else {
        if (cmax == r) {
            out.h = 60.0f * std::fmod(((g - b) / delta), 6.0f);
        } else if (cmax == g) {
            out.h = 60.0f * (((b - r) / delta) + 2.0f); 
        } else if (cmax == b) {
            out.h = 60.0f * (((r - g) / delta) + 4.0f);
        }
    }

    if (out.h < 0.0f) out.h += 360.0f;
    return out;
}