import sys, pygame
import random
import math

pygame.init()

width = 1080
height = 720
screen = pygame.display.set_mode( (width, height) )
clock = pygame.time.Clock()

class Snake:
    def __init__( self ):
        self.x = 100
        self.y = 100
        self.x_speed = 0
        self.y_speed = 0
        self.segments = []

        self.w = 10
        self.h = 10

    def draw( self, screen ):
        # add code to draw the snake head as a rectangle
        # based on the snakes x,y,w,h
        # ... ( DO THIS FIRST :) )

        # add a for loop to go through all the segments
        # and draw them as rectangles based on segment[0] and segment[1] and w and h
        # ....

        print("draw")  # delete this line when you get here

    def update( self ):
        # check if the x_speed and y_speed are 0 then return the function
        # ...

        # loop through the segments starting from the last segments (tail)
        # and stopping at the segment right before the first one
        # set the position of the segment to the position of the segment after it (closer to the head)
        # ...

        # if there are more than 0 segments, set the position of the first segement
        # to the position of the head (self.x, self.y)
        # ...

        self.x += self.x_speed*self.w
        self.y += self.y_speed*self.h

    def add_segment( self ):
        # write an if...else here that does the following
        # if there are 0 segments, add a new segment with position: [x-w, y]
        # otherwise add a new segment based on the last segments positions [last_seg[0]-w, last_seg[1]]
        # ...

        print("add segment") # delete this line when you get here

    def check_loss( self ):
        # loop through all the segments, check if the positions are
        # the same as the head, if true, then you have collided and should quit()
        # ...
        print("check_loss") # delete this line when you get here

snake = Snake()
snake.add_segment()

food_pos = [300, 300]
food_size = 50

# download and use a food image you want!
# apple.png probably does not exist for you
food_image = pygame.image.load('apple.png')
food_image = pygame.transform.scale(food_image, (food_size, food_size))

while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            sys.exit()

        if event.type == pygame.KEYDOWN:

            if event.key == pygame.K_DOWN:
                snake.x_speed = 0
                snake.y_speed = 1

            # add 3 more if statement here to handle all the other arrow keys
            # ...

    snake.update()
    snake.check_loss()

    # write 4 if statements to check if
    # the snakes head position is inside the food
    # if that is true, change the food position and add a segment to the snake
    # ...

    screen.fill( (0, 0, 0) )

    screen.blit(food_image, (food_pos, food_pos))

    snake.draw( screen )

    pygame.display.flip()

    clock.tick(30)
