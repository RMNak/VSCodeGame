import pygame
import sys
from PIL import Image, ImageDraw
import turtle

import matplotlib.pyplot as plt
import matplotlib.animation as animation
import numpy as np

fig, ax = plt.subplots()
x = np.linspace(0, 2*np.pi, 100)
line, = ax.plot(x, np.sin(x))

def animate(frame):
    line.set_ydata(np.sin(x + frame/10))
    return line,

ani = animation.FuncAnimation(fig, animate, frames=100, interval=50, blit=True)
plt.show()

pygame.init()
screen = pygame.display.set_mode((800, 600))
clock = pygame.time.Clock()

x, y = 400, 300
velocity_x, velocity_y = 5, 3

frames = []
for i in range(10):
    img = Image.new('RGB', (200, 200), color=(255, 255, 255))
    draw = ImageDraw.Draw(img)
    draw.ellipse([i*20, i*20, 100+i*20, 100+i*20], fill=(255, 0, 0))
    frames.append(img)

frames[0].save('animation.gif', save_all=True, append_images=frames[1:], 
               duration=100, loop=0)

turtle_screen = turtle.Screen()
turtle_screen.bgcolor("black")
t = turtle.Turtle()
t.speed(0)
t.color("cyan")

for i in range(360):
    t.forward(i)
    t.left(59)

turtle_screen.mainloop()

while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()
    
    # Update position
    x += velocity_x
    y += velocity_y
    
    # Bounce off edges
    if x <= 0 or x >= 800:
        velocity_x *= -1
    if y <= 0 or y >= 600:
        velocity_y *= -1
    
    # Draw
    screen.fill((0, 0, 0))
    pygame.draw.circle(screen, (255, 0, 0), (int(x), int(y)), 20)
    pygame.display.flip()
    clock.tick(60)