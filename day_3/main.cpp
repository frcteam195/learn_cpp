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
    }

    ~Particle(){}

    float size;
    int r;
    int g;
    int b;
    int a;
    float x;
    float y;
};


int main( )
{

    srand(time(NULL));

    Graphics graphics(800, 800);
    float angle = 0;


    std::vector<Particle> list_of_parts;

    for(int i = 0; i < 100; i++ )
    {
        Particle my_particle = Particle();
        my_particle.x = rand() % 800;
        my_particle.y = rand() % 800;
        list_of_parts.push_back( my_particle );
    }

    std::cout << list_of_parts.size() << "\n";

    while( graphics.is_running() )
    {
        graphics.clear();

        for(int i = 0; i < list_of_parts.size(); i++)
        {
            graphics.circle( list_of_parts[i].x, list_of_parts[i].y, list_of_parts[i].size,
                             list_of_parts[i].r, list_of_parts[i].g, list_of_parts[i].b, list_of_parts[i].a,
                             false );
        }

        graphics.draw();
    }
}
