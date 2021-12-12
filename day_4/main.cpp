#include "graphics.h"
#include "vec.h"
#include <iostream>

Graphics graphics = Graphics(800, 800);

float gravity = 5.8;

class MassSpring{
public:
    MassSpring( vec2<float> start ){
        mass = 2 ;
        spring_x = 0;
        spring_k = 0.1;
        spring_rest_len = 50;

        pos_of_spring_start = start;
        pos_of_spring_end = vec2<float>(0, 200) + start;

        vel_of_mass = vec2<float>(0,0);
        pos_of_mass = pos_of_spring_end;
    }

    void update(){
        vec2<float> spring_vector = pos_of_spring_end - pos_of_spring_start;
        float length_spring = spring_vector.length();
        float force_spring = (length_spring - spring_rest_len) * spring_k;

        vec2<float> force_on_mass = spring_vector.normalize()* force_spring * -1;

        force_on_mass = vec2<float>( 0, gravity ) + force_on_mass;

        vec2<float> accel_mass = force_on_mass / mass;

        vel_of_mass += accel_mass;
        vel_of_mass *= 0.95;
        pos_of_mass += vel_of_mass;

        pos_of_spring_end = pos_of_mass;

    }

    void set_pos( vec2<float> p ){
        pos_of_mass = p;
        pos_of_spring_end = pos_of_mass;
        vel_of_mass = vec2<float>(0,0);

    }

    void draw(){
        graphics.line( pos_of_spring_start.x, pos_of_spring_start.y,
                       pos_of_spring_end.x, pos_of_spring_end.y );

        graphics.circle( pos_of_mass.x, pos_of_mass.y, 10 );

    }

    float mass;
    float spring_x;
    float spring_k;
    float spring_rest_len;

    vec2<float> pos_of_spring_start;
    vec2<float> pos_of_spring_end;

    vec2<float> vel_of_mass;
    vec2<float> pos_of_mass;
};


int main()
{
    MassSpring p1(vec2<float>(100, 100));
    MassSpring p2(vec2<float>(300, 100));
    MassSpring p3(vec2<float>(500, 100));
    MassSpring p4(vec2<float>(200, 200));
    MassSpring p5(vec2<float>(600, 300));

    p2.spring_rest_len = 200;


    while( graphics.is_running() )
    {

        //update everything
        p1.update();
        p2.update();
        p3.update();
        p4.update();
        p5.update();

        if( graphics.is_L_mouse_down() ){
            p1.set_pos( vec2<float>(graphics.get_mouse_x(), graphics.get_mouse_y()) );
            p2.set_pos( vec2<float>(graphics.get_mouse_x(), graphics.get_mouse_y()) );
            p3.set_pos( vec2<float>(graphics.get_mouse_x(), graphics.get_mouse_y()) );
            p4.set_pos( vec2<float>(graphics.get_mouse_x(), graphics.get_mouse_y()) );
            p5.set_pos( vec2<float>(graphics.get_mouse_x(), graphics.get_mouse_y()) );
        }


        graphics.clear();
        p1.draw();
        p2.draw();
        p3.draw();
        p4.draw();
        p5.draw();
        graphics.draw();
    }
}


