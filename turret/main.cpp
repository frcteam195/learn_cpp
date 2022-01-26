#include "graphics.h"
#include "vec.h"
#include <iostream>
#include <math.h>

Graphics graphics = Graphics(1200, 900);

#define DEG_TO_RAD (M_PI/180.0)
#define RAD_TO_DEG (180.0/M_PI)


float get_turret_theta( float x, float y,
                        float robot_speed, float robot_theta, float dt,
                        float target_x, float target_y )
{
    float robot_pred_x = x + robot_speed * cos(robot_theta * DEG_TO_RAD) * dt;
    float robot_pred_y = y - robot_speed * sin(robot_theta * DEG_TO_RAD) * dt;
    float theta = 2*M_PI - atan2 (target_y-robot_pred_y, (target_x-robot_pred_x));


    theta = theta * RAD_TO_DEG;
    return theta;
}

int main()
{

    float x = 10;
    float y = 10;
    float robot_speed = 0;
    float robot_theta = 0;
    float theta = 0;
    float padding = 200;
    float target_x = 324;
    float target_y = 162;



    while( graphics.is_running() )
    {

        float dt = 10;
        theta = get_turret_theta(x, y,
                                 robot_speed,
                                 robot_theta,
                                 dt,
                                 target_x, target_y);

        std::cout << theta << "\n";
        graphics.clear();

        robot_speed = 0;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            robot_theta += 1;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            robot_theta -= 1;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            robot_speed = 2;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            robot_speed = -2;
        }



        float robot_pred_x = x + robot_speed*cos( (robot_theta) * DEG_TO_RAD )*dt;
        float robot_pred_y = y - robot_speed*sin( (robot_theta) * DEG_TO_RAD )*dt;


        x += robot_speed*cos( (robot_theta) * DEG_TO_RAD );
        y += -1*robot_speed*sin( (robot_theta) * DEG_TO_RAD );

        graphics.circle( target_x + padding, target_y + padding, 40 );

        graphics.rect( 648/2 + padding, 324/2 + padding,
                       648, 324,
                       0,
                       0,255,0,255,
                       true);

        graphics.rect( x + padding, y + padding, 10, 10, -1*robot_theta, 0,0,0,255, false );

        graphics.rect( robot_pred_x + padding, robot_pred_y + padding,
                       10, 10, -1*robot_theta, 0,0,0,110, false );

        graphics.line( robot_pred_x + padding, robot_pred_y + padding,
                       robot_pred_x + padding + 1000*sin( (theta+90) * DEG_TO_RAD ),
                       robot_pred_y + padding + 1000*cos( (theta+90) * DEG_TO_RAD ),
                       255,0,255,255);

        graphics.line( x + padding, y + padding,
                       x + padding + 100*sin( (robot_theta+90) * DEG_TO_RAD ),
                       y + padding + 100*cos( (robot_theta+90) * DEG_TO_RAD ),
                       0,0,255,255);


        graphics.draw();
    }
}


