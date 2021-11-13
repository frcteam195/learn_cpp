#include "graphics.h"

#include <iostream>


class Particle{
public:

    Particle()
    {
	x = 0;
	y = 0;
	vx = 0;
	vy = 2;
	ax = 0;
	ay = 0;
	r = 100;
	g = 100;
	b = 100;
	a = 255;
	size = 5;
	angle = 0;
    }

    ~Particle(){}

    float x;
    float y;
    float vx;
    float vy;
    float ax;
    float ay;
    int lifetime;
    int r;
    int g;
    int b;
    int a;
    float size;
    float angle;
};

float rand_f( float start, float end )
{
    float range = end - start;
    int mod = range * 10000;
    int random_int = rand() % mod;
    return (random_int / 10000.0) + start;
}


int main( int argc, char** argv )
{
    srand(time(nullptr));

    Graphics graphics(800, 800);
    static float angle = 0;

    std::vector<Particle> particles;

    while( graphics.is_running() )
    {

	graphics.clear();

	for( int i = 0; i < particles.size(); i++ )
	{
	    if( particles[i].size < 1 )
	    {
		particles.erase( particles.begin()+i );
	        continue;
	    }

	    graphics.rect( particles[i].x, particles[i].y,
			   particles[i].size, particles[i].size,
			   particles[i].angle,
			   particles[i].r, particles[i].g, particles[i].b, particles[i].a,
			   false );

	    particles[i].x += particles[i].vx;
	    particles[i].y += particles[i].vy;
	    particles[i].vx += particles[i].ax;
	    particles[i].vy += particles[i].ay;
	    particles[i].a = particles[i].a * 0.998;
	    particles[i].size = particles[i].size * 0.995;
	    particles[i].angle += rand()%10;
	}

	if( graphics.is_L_mouse_down() )
	{
	    Particle part;
	    for( int i = 0; i < 3; i++ )
	    {
		part.x = graphics.get_mouse_x() + rand()%20 - 10;
		part.y = graphics.get_mouse_y() + rand()%20 - 10;
		part.vx = rand_f(-0.5, 0.5);
		part.vy = rand_f(-2.0, -1);
		part.r = 150 + rand()%20;
		part.g = 150 + rand()%20;
		part.b = 150 + rand()%20;
		part.a = (rand() % 50 ) + 100;
		part.size = rand() % 20 + 5;

		particles.push_back( part );

		part.x = graphics.get_mouse_x() + rand()%20 - 10;
		part.y = graphics.get_mouse_y() + rand()%20 - 10;
		part.vx = rand_f(-0.9, 0.9);
		part.vy = rand_f(-1.5, -0.5);
		part.r = 232;
		part.g = (rand() % 40) + 110;
		part.b = 49;
		part.a = (rand() % 50 ) + 205;
		part.size = rand() % 20 + 10;

		particles.push_back( part );
	    }

	    graphics.rect( graphics.get_mouse_x(),
			   graphics.get_mouse_y(),
			   20, 20,
			   angle,
			   255, 0, 255, 255,
			   true );

	    angle += 1;
	}

	graphics.draw();
    }
}
