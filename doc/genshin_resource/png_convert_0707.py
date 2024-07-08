from PIL import Image
import os

# 设置输入和输出文件夹路径
input_folder = '素材'
output_folder = 'output'

# 确保输出文件夹存在
if not os.path.exists(output_folder):
    os.makedirs(output_folder)

# 设置阈值（例如，200）
threshold = 200

# 遍历输入文件夹中的所有BMP文件
for filename in os.listdir(input_folder):
    if filename.endswith('.bmp'):
        # 打开BMP文件
        input_path = os.path.join(input_folder, filename)
        img = Image.open(input_path).convert('RGBA')

        # 获取像素数据
        pixels = img.load()

        # 遍历所有像素并设置低于阈值的像素为透明
        for i in range(img.size[0]):
            for j in range(img.size[1]):
                r, g, b, a = pixels[i, j]
                if r < threshold and g < threshold and b < threshold:
                    pixels[i, j] = (r, g, b, 0)  # 设置为透明

        # 保存为PNG文件
        output_path = os.path.join(output_folder, os.path.splitext(filename)[0] + '.png')
        img.save(output_path)

print("处理完成！")