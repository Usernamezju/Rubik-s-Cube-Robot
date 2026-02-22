import cv2
import time
import cube_engine  # 你的 C++ 加速模块
from classify_color import classify_color
from kociemba import get_solve_steps

def main():
    # 1. 初始化
    # 提示：打开索引为 0 的摄像头，并实例化 C++ 导出的串口类
    cap = cv2.VideoCapture(0, cv2.CAP_V4L2)

    # 2. 必须在读取前设置像素格式为 MJPG
    # 四字符代码 (FourCC) 是关键
    cap.set(cv2.CAP_PROP_FOURCC, cv2.VideoWriter_fourcc(*'MJPG'))

    # 3. 设置分辨率 (640x480 是性能和识别精度的黄金平衡点)
    cap.set(cv2.CAP_PROP_FRAME_WIDTH, 640)
    cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 480)
    serial = cube_engine.RobotSerial
    
    cube_state = []
    
    print("--- 浙大魔方机器人系统已就绪 ---")

    print("按下 's' 键记录一个面的颜色")
    while True:
        ret, frame = cap.read()
        if not ret: break

        # 2. 调用 C++ 计算 9 个采样点的坐标
        # 提示：传入帧的宽度(frame.shape[1])、高度(frame.shape[0])和步长 60
        points = cube_engine.calculate_grid_points(frame.shape[1], frame.shape[0], 60)

        current_face_colors = []
        for p in points:
            # 3. 调用 C++ 计算该坐标点周围的平均 HSV 值
            # 提示：传入图像 frame，坐标 p.x, p.y，以及采样半径 5
            hsv = cube_engine.get_average_hsv(frame, p.x, p.y, 5)
            
            # 4. 调用 Python 逻辑判断颜色名
            color_name = classify_color(hsv.h, hsv.s, hsv.v)
            current_face_colors.append(color_name)

            # 在画面上绘制辅助 UI
            cv2.circle(frame, (p.x, p.y), 10, (0, 255, 0), 2)

        cv2.imshow("Vision Task", frame)
        key = cv2.waitKey(1)

        # 5. 触发逻辑：按下 's' 键记录一个面的颜色
        if key == ord('s'):
            if len(cube_state) < 54:
                cube_state.extend(current_face_colors) # 提示：将 9 个颜色加入总列表
                print(f"当前面记录成功，已有 {len(cube_state)} 个色块")
            
            # 6. 当凑齐 54 个色块时，启动求解程序
            if len(cube_state) == 54:
                # 调用 Kociemba 算法计算解法字符串
                solution = get_solve_steps(cube_state)
                
                if "Error" in solution:
                    print("魔方状态非法，请按 Q 退出重新扫描")
                    cube_state = [] 
                else:
                    print(f"解法步骤: {solution}")
                    
                    # 7. 调用 C++ 将 "R2 U F'" 这种解法解析为动作结构体列表
                    moves = cube_engine.parse_solution(solution)
                    
                    # 8. 执行动作循环
                    for m in moves:
                        # 映射旋转 ID：90->1, 180->2, -90->3
                        angle_id = 1 if m.degrees == 90 else (2 if m.degrees == 180 else 3)
                        
                        # 提示：调用串口对象的发送函数，传入执行的面和角度 ID
                        serial.sendMove(m.face, angle_id)
                        
                        time.sleep(0.5) # 给电机物理转动的时间
                    
                    cube_state = [] # 清空，准备下次任务

        elif key == ord('q'):
            break

    cap.release()
    cv2.destroyAllWindows()

if __name__ == "__main__":
    main()