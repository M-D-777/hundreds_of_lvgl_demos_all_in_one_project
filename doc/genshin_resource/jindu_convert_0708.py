from PIL import Image
import os

def merge_images(image_paths, output_path):
    # 打开所有图片
    images = [Image.open(path) for path in image_paths]
    
    # 计算拼接后的总宽度
    total_width = sum(image.width for image in images)
    max_height = max(image.height for image in images)
    
    # 创建一个新的空白图片
    new_image = Image.new('RGBA', (total_width, max_height), (0, 0, 0, 0))
    
    # 将所有图片水平拼接
    x_offset = 0
    for image in images:
        new_image.paste(image, (x_offset, 0))
        x_offset += image.width
    
    # 处理像素：将透明像素替换为白色非透明，其他像素处理为全透明
    data = new_image.getdata()
    new_data = []
    for item in data:
        if item[3] == 0:  # 透明像素
            new_data.append((255, 255, 255, 255))  # 白色非透明
        else:
            new_data.append((0, 0, 0, 0))  # 全透明
    
    new_image.putdata(new_data)
    
    # 保存拼接后的图片
    new_image.save(output_path)

# 获取素材文件夹中的所有图片路径
input_folder = '素材'
output_folder = 'output'
os.makedirs(output_folder, exist_ok=True)
image_paths = [os.path.join(input_folder, f'{i}.png') for i in range(1, 8)]
output_path = os.path.join(output_folder, 'output.png')

# 调用函数进行图片拼接和处理
merge_images(image_paths, output_path)