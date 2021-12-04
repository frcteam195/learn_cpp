#include "graphics.h"
#include "vec.h"
#include <iostream>

Graphics graphics = Graphics(800, 800);

int main()
{
    while( graphics.is_running() )
    {
        graphics.clear();
        graphics.draw();
    }
}


