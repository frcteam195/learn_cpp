#include "graphics.h"
#include "vec.h"
#include <iostream>
#include <math.h>

Graphics graphics = Graphics(1200, 900);


int main()
{

    while( graphics.is_running() )
    {
        graphics.draw();
    }
}


