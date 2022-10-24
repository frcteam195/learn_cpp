import sys, pygame
import random
import math

pygame.init()

width, height = 1080, 720
screen = pygame.display.set_mode( (width, height) )

rand_range_x = 7
jitter_x_num = 0.1

def draw_circle_alpha(surface, color, center, radius):
    target_rect = pygame.Rect(center, (0, 0)).inflate((radius * 2, radius * 2))
    shape_surf = pygame.Surface(target_rect.size, pygame.SRCALPHA)
    pygame.draw.circle(shape_surf, color, (radius, radius), radius)
    surface.blit(shape_surf, target_rect)

class Particle:
    def __init__(self, x_in, y_in, radius_in):
        self.x = x_in
        self.y = y_in
        self.radius = radius_in
        self.vx = random.randint(-1*rand_range_x, rand_range_x) * 0.2
        self.vy = random.randint(-6, -3) * 0.5
        self.color = (255,
                      random.randint(0, 200),
                      100,
                      100)

        self.jitter_x = 0;

    def update( self ):
        self.x = self.x + self.vx + math.sin(self.jitter_x)
        self.y = self.y + self.vy
        self.radius = self.radius*0.99
        self.jitter_x += jitter_x_num


particles = []
mouse_x = 200
mouse_y = 200

while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            sys.exit()

        if event.type == pygame.MOUSEMOTION:
            mouse_x = event.pos[0]
            mouse_y = event.pos[1]

        if event.type == pygame.KEYDOWN:
            if event.unicode == "+" :
                rand_range_x += 1
            if event.unicode == "-" :
                rand_range_x -= 1

            if event.key == pygame.K_UP:
                jitter_x_num += 0.1

            if event.key == pygame.K_DOWN:
                jitter_x_num -= 0.1

    screen.fill( (0, 0, 0, 100) )

    for particle in particles:
        draw_circle_alpha( screen,
                           particle.color,
                           (particle.x, particle.y),
                           particle.radius )

        particle.update()

    for i in range( 10 ):
        part = Particle(mouse_x, mouse_y, random.randint(8,15))
        particles.append( part )

    for particle in particles:
        if particle.radius < 0.5:
            particles.remove(particle)

    pygame.display.flip()
