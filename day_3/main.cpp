#include "graphics.h"
#include "stdlib.h"
#include <vector>
#include <list>
#include <math.h>

#include <iostream>

Graphics graphics(800, 800);

std::vector<uint32_t> generate_good_color()
{
	std::vector<uint32_t> colors;
	for(int i = 0; i < 3; i++)
		colors.push_back(0);

	uint32_t colorvalue = rand() % 768;
	if(colorvalue < 255)
	{
		colors[0] = (colorvalue + 127) % 255;
		colors[1] = colorvalue % 255;
		colors[2] = colorvalue % 255;
	}
	else if (colorvalue < 512)
	{
		colors[0] = colorvalue % 255;
		colors[1] = (colorvalue + 127) % 255;
		colors[2] = colorvalue % 255;
	}
	else
	{
		colors[0] = colorvalue % 255;
		colors[1] = colorvalue % 255;
		colors[2] = (colorvalue + 127) % 255;
	}
	return colors;
}

class Particle
{
	public:
	Particle(float x, float y)
	{
		this->x = x;
		this->y = y;
		size = (rand() % 100) / 10.0;
		std::vector<uint32_t> color = generate_good_color();
		x_speed = ((rand() % 100) / 3.0) - 16.5;
		y_speed = ((rand() % 100) / 3.0) - 16.5;

		r = color[0];
		g = color[1];
		b = color[2];
		a = 255;
	}

	void step()
	{
		y_speed = y_speed + (1.5);
		x = x + x_speed;
		y = y + y_speed;
		
		graphics.circle(x, y, size, r, g, b, a, false);
	}

	bool out_of_bounds()
	{
		if ( x < 0 || y < 0 || x > 800 || y > 800)
			return true;
		return false;
	}

	private:
	float size;
	int r,g,b,a;
	float x,y;
	float x_speed;
	float y_speed;
};

class RotatingSquare
{
	public:
	RotatingSquare(float progress)
	{
		this->progress = progress;
		colors.push_back(255);
		colors.push_back(0);
		colors.push_back(0);
		colors.push_back(255);
		colors.push_back(0);
		colors.push_back(0);

		x = 400 + (sin(progress) * 200.0);
		y = 400 + (cos(progress) * 200.0);

		colorvalue = 0;
		speed = 3;
		speed2 = 15;
		sign = 1;

	}

	void step()
	{
		progress += 0.01;
		
		x = 400 + (sin(progress) * 200.0);
		y = 400 + (cos(progress) * 200.0);

		colorvalue += rand() % 20;
		colorvalue = colorvalue % 768;

		if(colorvalue < 255)
		{
			colors[0] = (colorvalue + 127) % 255;
			colors[1] = colorvalue % 255;
			colors[2] = colorvalue % 255;
			colors[5] = (colorvalue + 127) % 255;
			colors[4] = colorvalue % 255;
			colors[3] = colorvalue % 255;
		}
		else if (colorvalue < 512)
		{
			colors[0] = colorvalue % 255;
			colors[1] = (colorvalue + 127) % 255;
			colors[2] = colorvalue % 255;
			colors[5] = colorvalue % 255;
			colors[4] = (colorvalue + 127) % 255;
			colors[3] = colorvalue % 255;
		}
		else
		{
			colors[0] = colorvalue % 255;
			colors[1] = colorvalue % 255;
			colors[2] = (colorvalue + 127) % 255;
			colors[3] = colorvalue % 255;
			colors[4] = colorvalue % 255;
			colors[5] = (colorvalue + 127) % 255;
		}

		std::cout << "X: " << x << " Y: " << y << std::endl;

		graphics.rect( x,
			y,
			200, 200,
			angle,
			colors[0], colors[1], colors[2], 255,
			true );

		graphics.rect( x,
			y,
			50, 50,
			-angle2,
			colors[3], colors[4], colors[5], 255,
			true );
				
		speed += ((rand() % 2) * 0.1) * sign;
		if (speed > 30 || speed < 3)
		{
			sign = -sign;
		}
		angle += speed;

		speed2 += ((rand() % 2) * 0.1) * sign;
		if (speed2 > 30 || speed2 < 3)
		{
			sign = -sign;
		}
		angle2 += speed2;


		Particle new_particle = Particle(x, y);
		for(int i = 0;
			i < 10;
			i++)
		{
			particles.push_back(new_particle);
		}
		
		std::list<std::list<Particle>::iterator> to_delete;

		for (std::list<Particle>::iterator i = particles.begin();
			i != particles.end();
			i++)
		{
			(*i).step();
			if ((*i).out_of_bounds())
				to_delete.push_back(i);
		}
		for (std::list<std::list<Particle>::iterator>::iterator i = to_delete.begin();
			i != to_delete.end();
			i++)
		{
			particles.erase((*i));
		}
	}

	private:
	float progress;
	float angle;
	float angle2;
	uint32_t x, y;
	std::vector<uint32_t> colors;
	std::list<Particle> particles;
	uint32_t colorvalue;
	float speed = 3;
	float speed2 = 15;
	int32_t sign = 1;
};


int main( int argc, char** argv )
{

	std::vector<RotatingSquare> squares;
	for(int i = 0; i < 4; i++)
	{
		float progress = M_PI_2 * (float) i;
		std::cout << "Squares " << progress << std::endl;
		RotatingSquare square = RotatingSquare(progress);
		squares.push_back(square);
	}
    while( graphics.is_running() )
    {
		graphics.clear();
		for(std::vector<RotatingSquare>::iterator i = squares.begin();
		    i != squares.end();
			i++)
		{
			(*i).step();	
		}
		graphics.draw();
    }
}
