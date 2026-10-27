import pygame
import sys

pygame.init()
screen = pygame.display.set_mode((800, 600))
clock = pygame.time.Clock()

x, y = 400, 300
velocity_x, velocity_y = 5, 3

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