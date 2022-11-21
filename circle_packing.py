import pygame
import random
import math
import sys
from PIL import Image

pygame.init()

class Circle:
    def __init__( self, in_x, in_y, col_in ):
        self.x = in_x
        self.y = in_y;
        self.radius = 1;
        self.should_grow = True
        self.col = col_in


    def grow( self ):
        if self.should_grow:
            self.radius += 1

    def draw( self, screen ):
        pygame.draw.circle(screen,
                           self.col,
                           (self.x, self.y),
                           self.radius,
                           width=1)


width, height = 1080, 720
screen = pygame.display.set_mode( (width, height) )
clock = pygame.time.Clock()
new_add_fail_count = 0

circles = []

positions = []


img = Image.open('picture.png')
img = img.resize( (900, 708) )
pix = img.load()
print(img.size)
print(pix[0,0])

for r in range(img.size[0]):
    for c in range(img.size[1]):
        if pix[r,c][3] > 0:
            positions.append( {"x":r, "y":c, "color":pix[r,c]} )

def is_inside( x, y, circle ):
    dist_x = circle.x - x;
    dist_y = circle.y - y;

    length_sqr = dist_x*dist_x + dist_y*dist_y

    if( length_sqr < (circle.radius*circle.radius) + 5 ):
        return True

    return False


def dist( c1, c2 ):
    dist_x = c1.x - c2.x;
    dist_y = c1.y - c2.y;
    return math.sqrt(dist_x*dist_x + dist_y*dist_y)


def check_pos( x, y ):
    for c in circles:
        if is_inside( x, y, c ):
            return False
    return True

def add_circle( ):
    global new_add_fail_count

    '''
    x = random.randint(0, width)
    y = random.randint(0, height)

    if( check_pos( x, y ) ):
        circles.append( Circle(x,y) )
        new_add_fail_count = 0
    else:
        new_add_fail_count += 1
    '''

    if len(positions) <= 0:
        new_add_fail_count += 1
        return

    index = random.randint(0, len(positions))
    x = positions[index]["x"]
    y = positions[index]["y"]

    if check_pos( x, y ):

        color = positions[index]["color"]
        circles.append( Circle(x, y, color ) )
        positions.pop( index )
        new_add_fail_count = 0
    else:
        new_add_fail_count += 1


while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            sys.exit()

    screen.fill( (0, 0, 0, 255) )

    for i in range(20):
        if new_add_fail_count < 100:
            add_circle()

    for c in circles:
        for c_other in circles:
            if c_other != c:
                if dist( c, c_other ) < c.radius + c_other.radius:
                    c.should_grow = False
                    c_other.should_grow = False

        c.grow()
        c.draw( screen )

    pygame.display.flip()
    clock.tick(120)
