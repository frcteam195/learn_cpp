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
	    graphics.line( 200, 200,
			   graphics.get_mouse_x(), graphics.get_mouse_y(),
			   255, 0, 0, 255);


	    /*graphics.circle( graphics.get_mouse_x(),
			     graphics.get_mouse_y(),
			     20,
			     255, 0, 0, 120,
			     true);
	    */


	    graphics.rect( graphics.get_mouse_x(),
			   graphics.get_mouse_y(),
			   30, 50,
			   angle,
			   255, 0, 255, 255,
			   true );

	    angle += 0.01;
	}

	graphics.draw();
    }
}
