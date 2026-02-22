def classify_color(h, s, v):
    """
    根据给定的 HSV 值返回颜色字符串
    H: 0-360, S: 0-1, V: 0-1
    """
    # --- 填空 1: 判定白色 ---
    # 提示：白色非常亮，但颜色非常不“纯”（饱和度极低）。
    # 如果饱和度 S 小于 0.2，且亮度 V 大于 0.8，我们判定为白色。
    if s < 0.2 and v > 0.8:
        return "WHITE"

    # 对于其他彩色，我们主要观察 H (色相环)
    # 红色通常在 0° 附近或 360° 附近
    if (h < 10 or h > 350): 
        return "RED"
    
    # --- 填空 2: 判定橙色 vs 黄色 ---
    # 提示：橙色在色相环上介于红色和黄色之间（约 11-44°），
    # 黄色则在 45-70° 左右。
    elif 10 <= h < 45:
        return "ORANGE"
    elif 45 <= h < 70:
        return "YELLOW"

    # --- 填空 3: 判定绿色与蓝色 ---  
    # 提示：绿色在 70-150° 之间，蓝色在 170-250° 之间。   
    elif 70 <= h < 150:
        return "GREEN"
    elif 170 <= h < 250:
        return "BLUE"
    
    return "UNKNOWN"  


def build_cube_string(detected_colors):
    # 严谨检查：必须是 54 个颜色标签
    if len(detected_colors) != 54:
        return f"Error: Expected 54 colors, got {len(detected_colors)}"

    # 1. 提取中心块 (U, R, F, D, L, B)
    # 索引对应每个面的中心点
    try:
        centers = {
            detected_colors[4]:  'U', # 顶
            detected_colors[13]: 'R', # 右
            detected_colors[22]: 'F', # 前
            detected_colors[31]: 'D', # 底
            detected_colors[40]: 'L', # 左
            detected_colors[49]: 'B'  # 后
        }
        
        if len(centers) < 6:
            return "Error: Duplicate center colors (识别到了重复的中心颜色)"

        # 2. 生成 Kociemba 所需的面位字符串
        res = "".join([centers[color] for color in detected_colors])
        return res
        
    except KeyError as e:
        return f"Error: Color {e} has no corresponding center"

# --- 填空 2: 逻辑思考 ---
# 如果识别出的 54 个格子中，某种颜色（比如白色 'U'）的数量不是 9 个，
# 这意味着什么？
# 答案：________________________________