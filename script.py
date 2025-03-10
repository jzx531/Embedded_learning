# import socket
# import cv2
# import numpy as np
# import time
# import os
# import pyautogui

# from picture import picture

# screenshot = pyautogui.screenshot()
# frame = np.array(screenshot)
# shape = frame.shape
# print(shape[0])
# print(shape[1])
# resized_image = cv2.resize(frame, (int(shape[0]/40), int(shape[1]/40)), interpolation=cv2.INTER_AREA)
# print(resized_image.shape)
# print(resized_image)

# R_image = resized_image[:, :, 2]
# G_image = resized_image[:, :, 1]
# B_image = resized_image[:, :, 0]
# print(R_image)


from PIL import Image
import numpy as np

def rgb_to_rgb565(r, g, b):
    """将RGB值转换为RGB565格式"""
    return (r & 0xF8) << 8 | (g & 0xFC) << 3 | b >> 3

def process_image(img):
    # 缩放图像
    img= img.resize(40, 40)
    width, height = img.size
    # 转换图像数据
    img_data = np.array(list(img.getdata()), dtype=np.uint8)
    # print(img_data)
    print(len(img_data))
    img_565_data = []
    # for i in range(0, len(img_data)):
    for i in range(0, 1):
        r, g, b = img_data[i]
        print(r, g, b)
        print(rgb_to_rgb565(r, g, b))
        lowbit = rgb_to_rgb565(r, g, b) & 0xFF
        highbit = (rgb_to_rgb565(r, g, b) >> 8) & 0xFF
        img_565_data.append(lowbit)
        img_565_data.append(highbit)
    return img_565_data

def convert_image_to_16bit_bmp(input_path):
    # 打开输入图像
    img = Image.open(input_path).convert('RGB')
    # 获取图像尺寸
    return process_image(img)


img_565_data =  convert_image_to_16bit_bmp('xnh.jpg')
