#include "graphics.h"
#include "vec.h"
#include <iostream>

Graphics graphics = Graphics(800, 800);
float gravity = 0.5;
float damp_factor = 0.90;

class PointMass {
public:


    PointMass(){
        mass = 1;
        pos = vec2<float>(0,0);
        vel = vec2<float>(0,0);
        accel = vec2<float>(0,0);
    }

    PointMass(float m){
        mass = m;
        pos = vec2<float>(0,0);
        vel = vec2<float>(0,0);
        accel = vec2<float>(0,0);
    }

    void draw(){
        //graphics.circle( pos.x, pos.y, 2 );
    }

    void apply_force( vec2<float> force ){
        vec2<float> new_accel = force / mass;

        accel = new_accel;
        vel += accel;
        vel *= damp_factor;
        pos += vel;
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

    Spring():
        Spring( vec2<float>(100, 100),
                vec2<float>(100, 200),
                0.1 )
        {
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

class SpringChain{
public:

    SpringChain( vec2<float> _start_pos, float length, float resolution ){

        anchor_pos = _start_pos;
        float segment_len = length / resolution;
        for( int i = 0; i < resolution; i++ ){

            vec2<float> seg_pos_start = vec2<float>(0, i*segment_len) + _start_pos;
            vec2<float> seg_pos_end = vec2<float>(0, (i+1)*segment_len) + _start_pos;

            PointMass point = PointMass(5);
            point.pos = seg_pos_start;
            points.push_back( point );

            if( i < resolution -1 ){
                Spring spring = Spring( seg_pos_start, seg_pos_end, 0.05 );
                springs.push_back(spring);
            }
        }

    }

    void draw(){
        for(int i = 0; i < springs.size(); i++){
            springs[i].draw();
        }

        for(int i = 0; i < points.size(); i++){
            points[i].draw();
        }
    }

    void update(){
        for(int i = 0; i < springs.size(); i++){

            vec2<float> force = springs[i].get_force_dir()*springs[i].get_force();

            if(i != 0){
                points[i].apply_force(force*-1);
                points[i].apply_force( vec2<float>(0,gravity) );
            }

            points[i+1].apply_force(force);


            springs[i].start_pos = points[i].pos;
            springs[i].end_pos = points[i+1].pos;
        }
    }


    void set_end_pos( vec2<float> pos ){
        int max_point_i = points.size()-1;
        points[max_point_i].pos = pos;
        points[max_point_i].vel = vec2<float>(0,0);
        springs[max_point_i-1].end_pos = pos;
    }

    std::vector<PointMass> points;
    std::vector<Spring> springs;
    vec2<float> anchor_pos;
};


int main()
{
    SpringChain chain1( vec2<float>(0, 0), 150, 20);
    SpringChain chain2( vec2<float>(200, 0), 150, 20);
    SpringChain chain3( vec2<float>(400, 0), 150, 20);
    SpringChain chain4( vec2<float>(600, 0), 150, 20);
    SpringChain chain5( vec2<float>(800, 0), 150, 20);

    while( graphics.is_running() )
    {
        chain1.update();
        chain1.set_end_pos( vec2<float>(graphics.get_mouse_x(),graphics.get_mouse_y() ) );

        chain2.update();
        chain2.set_end_pos( vec2<float>(graphics.get_mouse_x(),graphics.get_mouse_y() ) );

        chain3.update();
        chain3.set_end_pos( vec2<float>(graphics.get_mouse_x(),graphics.get_mouse_y() ) );

        chain4.update();
        chain4.set_end_pos( vec2<float>(graphics.get_mouse_x(),graphics.get_mouse_y() ) );

        chain5.update();
        chain5.set_end_pos( vec2<float>(graphics.get_mouse_x(),graphics.get_mouse_y() ) );

        graphics.clear();
        chain1.draw();
        chain2.draw();
        chain3.draw();
        chain4.draw();
        chain5.draw();
        graphics.draw();
    }
}


