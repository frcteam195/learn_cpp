#include "graphics.h"
#include "vec.h"
#include <iostream>

Graphics graphics = Graphics(800, 800);

float gravity = 0;

class MassSpring{
public:
    MassSpring( vec2<float> start ){
        mass = 0.1;
        spring_x = 0;
        spring_k = 0.005;
        spring_rest_len = 20;

        pos_of_spring_start = start;
        pos_of_spring_end = vec2<float>(0, 200) + start;

        vel_of_mass = vec2<float>(0,0);
        pos_of_mass = pos_of_spring_end;
    }

    void update(){
        vec2<float> force_on_mass = get_spring_force();
        apply_force( get_spring_force() );
        apply_force( vec2<float>( 0, gravity ) );

        vel_of_mass *= 0.90;
        pos_of_mass += vel_of_mass;

        pos_of_spring_end = pos_of_mass;

    }

    void apply_force( vec2<float> force){
        vec2<float> accel_mass = force / mass;
        vel_of_mass += accel_mass;
    }

    vec2<float> get_spring_force(){
        vec2<float> spring_vector = pos_of_spring_end - pos_of_spring_start;
        float length_spring = spring_vector.length();
        float force_spring = (length_spring - spring_rest_len) * spring_k;

        return spring_vector.normalize()* force_spring * -1;
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

    MassSpring first( vec2<float>(200,400) );
    MassSpring middle( vec2<float>(200, 300) );
    MassSpring second_middle( vec2<float>(200, 300) );
    MassSpring last( vec2<float>(400, 400) );


    while( graphics.is_running() )
    {

        first.pos_of_spring_start = vec2<float>(400, 0);

        vec2<float> force_of_middle_spring = middle.get_spring_force();
        vec2<float> force_of_last_spring = last.get_spring_force();

        first.apply_force( force_of_middle_spring * -1 );
        middle.apply_force( force_of_last_spring * -1 );
        middle.pos_of_spring_start = first.pos_of_mass;



        last.pos_of_spring_start = middle.pos_of_mass;
        last.pos_of_mass = vec2<float>( graphics.get_mouse_x(), graphics.get_mouse_y());
        last.pos_of_spring_end = last.pos_of_mass;


        first.update();
        middle.update();

        graphics.clear();

        first.draw();
        last.draw();
        middle.draw();

        graphics.draw();
    }
}


