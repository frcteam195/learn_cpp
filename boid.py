import sys, pygame
import math
import random

pygame.init()

visibility = 50
mouse_x = 0;
mouse_y = 0

max_speed = 5

size = width, height = 1920, 1080
screen = pygame.display.set_mode(size)
clock = pygame.time.Clock()
boids = []

class Boid:
    def __init__(self, x, y):
        self.x = x;
        self.y = y;
        self.vx = random.randint(-5,5);
        self.vy = random.randint(-5,5);

        self.trail = []

    def draw(self, screen):
        if len( self.trail ) > 1:
            pygame.draw.lines( screen,
                               (0,255,0,0),
                               False,
                               self.trail )

        pygame.draw.circle( screen,
                            (255, 0, 255),
                            (self.x, self.y),
                            5 )


    def update(self):

        self.trail.append( (self.x, self.y) )
        if len( self.trail ) > 10:
            self.trail.pop(0)


        self.x += self.vx
        self.y += self.vy


def fly_towards_center( boid ):
    v_change_percent = 0.001
    center_x = 0
    center_y = 0
    boid_num = 0

    for b in boids:
        if( dist(boid, b) < visibility ):
            center_x += b.x
            center_y += b.y
            boid_num += 1

    if( boid_num != 0 ):
        center_x = center_x / boid_num
        center_y = center_y / boid_num

    boid.vx += (center_x - boid.x) * v_change_percent
    boid.vy += (center_y - boid.y) * v_change_percent


def fly_towards_mouse( boid ):
    v_change_percent = 0.0005
    boid.vx += (mouse_x - boid.x) * v_change_percent
    boid.vy += (mouse_y - boid.y) * v_change_percent


def avoid_other_boids( boid_in ):

    avoid_change_percent = 0.05
    x_force = 0
    y_force = 0

    for b in boids:
        if( b != boid_in ):
            if( dist(boid_in, b) < 10 ):
                x_force += boid_in.x - b.x
                y_force += boid_in.y - b.y

    boid_in.vx += x_force * avoid_change_percent
    boid_in.vy += y_force * avoid_change_percent


def match_nearby_velocity( boid_in ):
    v_change_percent = 0.005
    vx_average = 0
    vy_average = 0
    num_boids = 0

    for b in boids:
        if( dist( boid_in, b ) < visibility ):
            vx_average += b.vx
            vy_average += b.vy
            num_boids += 1

    if num_boids > 0:
        vx_average = vx_average / num_boids
        vy_average = vy_average / num_boids

    boid_in.vx += (vx_average - boid_in.vx) * v_change_percent
    boid_in.vy += (vy_average - boid_in.vy) * v_change_percent


def dist( b1, b2 ):
    return math.sqrt((b1.x - b2.x)*(b1.x - b2.x) + (b1.y - b2.y)*(b1.y - b2.y))


for i in range( 0, 100 ):
    boids.append(Boid( random.randint(0,width),
                       random.randint(0,height )))


while True:

    for event in pygame.event.get():
        if event.type == pygame.QUIT: sys.exit()

        if event.type == pygame.MOUSEMOTION:
            mouse_x = event.pos[0]
            mouse_y = event.pos[1]

    screen.fill((0,0,0))

    for b in boids:
        b.draw(screen)
        b.update()

    for b in boids:
        fly_towards_center( b )
        fly_towards_mouse( b )
        avoid_other_boids( b )
        match_nearby_velocity( b )

    for b in boids:
        max_speed = 15;
        speed = math.sqrt(b.vx * b.vx + b.vy * b.vy);
        if speed > max_speed:
            b.vx = (b.vx / speed) * max_speed;
            b.vy = (b.vy / speed) * max_speed;

        if b.x > width:
            b.x = width
        if b.x < 0:
            b.x = 0
        if b.y > height:
            b.y = height
        if b.y < 0:
            b.y = 0


    pygame.display.flip()
    clock.tick(60)
