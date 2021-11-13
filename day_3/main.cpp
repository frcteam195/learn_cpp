#include "graphics.h"

#include <iostream>



int main( int argc, char** argv )
{
    Graphics graphics(800, 800);
    static float angle = 0;

    while( graphics.is_running() )
    {

	graphics.clear();

	if( graphics.is_L_mouse_down() )
	{

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
