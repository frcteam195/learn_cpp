#include "bounce.hpp"
#include <iostream>

void on_mouse_down( int button, int x, int y )
{
    set_x( x );
    set_y( y );
}

void step()
{
    if( (get_y() + get_r()) > get_window_height() )
    {
        set_vy( -1 * get_vy() );
    }

    if( (get_x() + get_r()) > get_window_width() )
    {
        set_vx( -1 * get_vx() );
    }

    if( (get_x() - get_r()) < 0 )
    {
        set_vx( -1 * get_vx() );
    }

}

int main()
{
    set_ball_color(255, 0, 255);
    set_bg_color(255, 255, 255);

    set_x( get_window_width() / 2  - get_r());
    set_y( get_window_height() / 2  - get_r() );

    set_ay(0.1);
    set_vx(20);

    run();
    return 0;
}
