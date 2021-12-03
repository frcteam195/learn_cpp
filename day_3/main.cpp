#include "graphics.h"
#include <iostream>


class Particle{
public:
    Particle()
    {
        size = 5;
        r = 255;
        g = 0;
        b = 255;
        a = 255;
        x = 200;
        y = 200;
		vx = 0;
		vy = 0;
    }

    ~Particle(){}

    float size;
    int r;
    int g;
    int b;
    int a;
    float x;
    float y;
	double vx;
	double vy;
};

double random_num( float start, float end )
{
    float range = end - start;
    int mod = range * 10000;
    int random_int = rand() % mod;
    return (random_int / 10000.0) + start;
}


int main( )
{
    srand(time(NULL));

	std::cout << random_num( 0.5, 1.5 ) << "\n";

    Graphics graphics(800, 800);
    float angle = 0;


    std::vector<Particle> list_of_parts;

	/*
    for(int i = 0; i < 100; i++ )
    {
		// center of screen  = 400, 400
        Particle my_particle = Particle();
        my_particle.x = random_num(350, 450);
        my_particle.y = random_num(350, 450);
		my_particle.vx = random_num( -2, 2 );
		my_particle.vy = random_num( -10, -5 );
		my_particle.size = random_num(5, 10);
        list_of_parts.push_back( my_particle );
    }*/


    while( graphics.is_running() )
    {
		for( int x = 0; x < 20; x++ ){
			Particle my_particle = Particle();
			my_particle.x = random_num( -50, 50 );
			my_particle.x += graphics.get_mouse_x();
			my_particle.y = random_num( -50, 50 );
			my_particle.y += graphics.get_mouse_y();
			my_particle.vx = random_num( -2, 2 );
			my_particle.vy = random_num( -10, -5 );
			my_particle.r = random_num(130, 200);
			my_particle.g = random_num(100, 130);
			my_particle.b = random_num(40, 60);
			my_particle.size = random_num(10, 20);
			list_of_parts.push_back( my_particle );
		}
	/*
		for( int x = 0; x < 5; x++ ){
			Particle my_particle = Particle();
			my_particle.x = random_num(350, 450);
			my_particle.y = random_num(350, 450);
			my_particle.vx = random_num( -2, 2 );
			my_particle.vy = random_num( -10, -5 );
			my_particle.r = random_num(100, 150);
			my_particle.g = random_num(100, 150);
			my_particle.b = random_num(100, 150);
			my_particle.size = random_num(5, 10);
			list_of_parts.push_back( my_particle );
		}
*/
	    std::cout << list_of_parts.size() << "\n";

        graphics.clear();

        for(int i = 0; i < list_of_parts.size(); i++)
        {
			if( list_of_parts[i].size < 0.05 )
			{
				list_of_parts.erase( list_of_parts.begin() + i );
				continue;
			}

            graphics.rect( list_of_parts[i].x, list_of_parts[i].y, list_of_parts[i].size, list_of_parts[i].size, 0,
                             list_of_parts[i].r, list_of_parts[i].g, list_of_parts[i].b, list_of_parts[i].a,
                             false );

			list_of_parts[i].x = list_of_parts[i].x + list_of_parts[i].vx;
			list_of_parts[i].y = list_of_parts[i].y + list_of_parts[i].vy;
			list_of_parts[i].size = list_of_parts[i].size * 0.97;
			list_of_parts[i].a = list_of_parts[i].a * 0.97;

        }

        graphics.draw();
    }
}
