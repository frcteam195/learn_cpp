#include "graphics.h"
#include "vec.h"
#include <iostream>

Graphics graphics = Graphics(800, 800);


class PointMass {
public:

    PointMass(){
        mass = 0.01;
    }

    void draw(){
        graphics.circle( pos.x, pos.y, 10 );
    }

    float mass; // mass in KG
    vec2<float> pos;
    vec2<float> vel;
    vec2<float> accel;
};


// hooks law states that the force produces by a spring is:
//   f = -kx;
//   where x is the distance the spring is extended
//   where k is the spring constant
//   where f is the force produces by the spring

class Spring {
public:

    Spring(){
        Spring( vec2<float>(100, 100),
                vec2<float>(100, 200),
                0.01 );
    }

    Spring( vec2<float> _pos,
            vec2<float> _endpos,
            float _k ){

        start_pos = _pos;
        end_pos = _endpos;
        k = _k;

        vec2<float> midpoint = ((end_pos - start_pos)/2);
        rest_length = midpoint.length();
    }

    void draw(){
        graphics.line( start_pos.x, start_pos.y,
                       end_pos.x, end_pos.y );
    }

    float get_force(){
        return -k*get_x();
    }

    vec2<float> get_force_dir(){
        return (end_pos - start_pos).normalize();
    }

    float get_x(){
        return (end_pos - start_pos).length() - rest_length;
    }

    vec2<float> start_pos;
    vec2<float> end_pos;
    float k;
    float rest_length;
};

class SpringMassAnchor{
public:

    SpringMassAnchor( vec2<float> pos ){

        vec2<float> end_pos = vec2<float>(pos.x, pos.y+100);

        spring = Spring( pos,
                         end_pos,
                         0.1 );

        ball = PointMass();
        ball.pos = end_pos;
        ball.mass = 1;

        gravity = 9.8;
    }

    void draw(){
        spring.draw();
        ball.draw();
    }

    void update(){

        vec2<float> gravity_force_on_ball = vec2<float>( 0, ball.mass*gravity );
        vec2<float> spring_force_on_ball = spring.get_force_dir()*spring.get_force();

        vec2<float> total_force_on_ball = gravity_force_on_ball + spring_force_on_ball;
        vec2<float> ball_accel = total_force_on_ball / ball.mass;

        float damp_factor = 0.99;
        ball.vel += ball_accel;
        ball.vel *= damp_factor;
        ball.pos += ball.vel;

        spring.end_pos = ball.pos;
    }


    void set_ball_pos( vec2<float> pos ){
        ball.pos = pos;
        spring.end_pos = pos;
        ball.vel = vec2<float>(0,0);
    }

    Spring spring;
    PointMass ball;
    float gravity;
};

int main()
{
    SpringMassAnchor sma = SpringMassAnchor( vec2<float>(400, 400) );

    while( graphics.is_running() )
    {
        sma.update();

        if( graphics.is_L_mouse_down() ){
            sma.set_ball_pos( vec2<float>(graphics.get_mouse_x(),graphics.get_mouse_y() ) );
        }

        graphics.clear();
        sma.draw();
        graphics.draw();
    }
}


