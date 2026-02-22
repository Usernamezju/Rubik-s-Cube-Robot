
#include "cube_vision.h"

// 假设这是一个串口类，我们手动实现其发送逻辑


void RobotSerial::sendMove(char face, int angle_id) {
        // 1. 将面字符映射为 ID
        unsigned char face_id = 0;
        if (face == 'U') face_id = 1;
        else if (face == 'R') face_id = 2;
        else if(face=='F') face_id=3;
        else if(face=='B') face_id=4;
        else if(face=='L') face_id=5;
        else  face_id=6;
        // 2. 准备数据包缓冲区
        // --- 填空 1: 定义缓冲区大小 ---
        // 提示：我们的协议包含 1 帧头 + 2 数据 + 1 帧尾 = 总计几字节？
        unsigned char packet[4];

        // 3. 填充协议内容
        packet[0] = 0xFF;        // 帧头
        packet[1] = face_id;     // 数据位1
        packet[2] = (unsigned char)angle_id; // 数据位2
        
        // --- 填空 2: 填充帧尾 ---
        // 提示：对应协议设计，帧尾是 0xFE
        packet[3] = 0xFE;

        // --- 填空 3: 调用发送接口 ---
        // 提示：发送我们刚刚填充好的 packet 数组
        this->sendRaw(packet, 4);
    }


void RobotSerial::sendRaw(const unsigned char* buffer, size_t length) {
        // 在真实环境下，这里会调用 Windows API (WriteFile) 
        // 或 Linux API (write)
        std::cout << "[Hardware] Sending bytes: ";
        for(size_t i = 0; i < length; ++i) {
            printf("0x%02X ", buffer[i]);
        }
        std::cout << std::endl;
    }

