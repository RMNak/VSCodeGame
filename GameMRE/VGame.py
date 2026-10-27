from PIL import Image, ImageDraw

frames = []
for i in range(10):
    img = Image.new('RGB', (200, 200), color=(255, 255, 255))
    draw = ImageDraw.Draw(img)
    draw.ellipse([i*20, i*20, 100+i*20, 100+i*20], fill=(255, 0, 0))
    frames.append(img)

frames[0].save('animation.gif', save_all=True, append_images=frames[1:], 
               duration=100, loop=0)