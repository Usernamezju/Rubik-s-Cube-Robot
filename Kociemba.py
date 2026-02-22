import kociemba
from classify_color import build_cube_string

def get_solve_steps(detected_colors):
    """
    detected_colors: 我们之前识别出的 54 个颜色名列表
    """
    # 1. 将颜色列表转化为 54 位面串（U, R, F, D, L, B）
    # 我们之前已经写好了映射逻辑 build_cube_string
    cube_string = build_cube_string(detected_colors)
    
    # 2. 调用 Kociemba 库获取解法
    try:
        # --- 填空 1: 调用核心函数 ---
        # 提示：传入生成的 54 位面串，获取解法。
        solution = kociemba.solve(cube_string)
        
        # --- 填空 2: 异常处理 ---
        # 提示：如果面串不符合逻辑（比如检测到 10 个红色块），算法会报错。
        # 我们需要在这里打印“识别错误”。
    except Exception as e:
        return f"Error: Invalid Cube State"

    return solution

# 示例输出： "D2 R' U2 L F B' ..."