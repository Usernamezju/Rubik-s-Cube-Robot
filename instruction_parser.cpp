#include <string>
#include <sstream>
#include "cube_vision.h"

std::vector<Move> parseSolution(std::string solution) {
    std::vector<Move> moves;
    std::stringstream ss(solution);
    std::string step;

    // 使用 stringstream 按空格分割字符串，例如 "R2" "U" "F'"
    while (ss >> step) {
        Move m;
        // --- 填空 1: 识别面 ---
        // 提示：字符串的第一个字符永远是代表面的字母。
        m.face = step[0];

        // 判定旋转角度
        if (step.length() == 1) {
            m.degrees = 90; // 顺时针 90
        } else if (step[1] == '2') {
            m.degrees = 180; // 180度
        } else if (step[1] == '\'') {
            // --- 填空 2: 逆时针处理 ---
            // 提示：逆时针通常表示为 -90 度。
            m.degrees = -90;
        }
        
        moves.push_back(m);
    }
    return moves;
}