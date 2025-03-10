import socket
import cv2
import numpy as np
import time
import os
import pyautogui

from picture import picture
from PIL import Image

from PIL import Image
import numpy as np


def rgb_to_rgb565(r, g, b):
    """将RGB值转换为RGB565格式"""
    return (r & 0xF8) << 8 | (g & 0xFC) << 3 | b >> 3

def process_image(img):
    img= img.resize((40, 40))
    width, height = img.size
    # 转换图像数据
    img_data = np.array(list(img.getdata()), dtype=np.uint8)
    print(len(img_data))
    img_565_data = []
    for i in range(0, len(img_data)):
    # for i in range(0, 1):
        r, g, b = img_data[i]
        # print(r, g, b)
        # print(rgb_to_rgb565(r, g, b))
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

# 定义服务器的 IP 和端口
SERVER_IP = "192.168.43.49"  # 服务器 IP
SERVER_PORT = 8000           # 服务器端口

def start_tcp_server(ip, port):
    # 创建 TCP socket
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    
    # 绑定 IP 和端口
    server_socket.bind((ip, port))
    
    # 开始监听，最多允许 5 个客户端连接
    server_socket.listen(5)
    print(f"TCP 服务器已启动，正在监听 {ip}:{port}...")

    while True:
        # 接受客户端连接
        client_socket, client_address = server_socket.accept()
        print(f"客户端 {client_address} 已连接")
        # client_socket.close()
        # print(f"客户端 {client_address} 连接已关闭")
        # break
        try:
            while True:
                # 接收客户端发送的数据
                data = client_socket.recv(1024)  # 每次最多接收 1024 字节
                if not data:
                    print(f"客户端 {client_address} 已断开连接")
                    break

                # 打印接收到的数据
                print(f"收到来自 {client_address} 的数据: {data.decode('GBK')}")

                # 向客户端发送响应（可选）
                # response = "已收到数据: " + data.decode('GBK')
                # client_socket.send(response.encode('GBK'))
                # 获取屏幕截图
                screenshot = pyautogui.screenshot()
                # 转换图像数据
                screen_565_data = process_image(screenshot)

                response = bytes(screen_565_data)
                # response = bytes(img_565_data)
                client_socket.send(response)
        except Exception as e:
            print(f"与客户端 {client_address} 通信时发生错误: {e}")
        finally:
            # 关闭客户端连接
            client_socket.close()
            print(f"客户端 {client_address} 连接已关闭")

if __name__ == "__main__":
    start_tcp_server(SERVER_IP, SERVER_PORT)