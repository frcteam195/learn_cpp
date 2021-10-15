#pragma once

void on_mouse_down( int button, int x, int y );
void step();
void init();
void run();


float get_window_width();
float get_window_height();
float get_r();

float get_x();
float get_y();
float get_vx();
float get_vy();
float get_ax();
float get_ay();

void set_ball_color( int r, int g, int b );
void set_bg_color( int r, int g, int b );

void set_max_vx( float in );
void set_max_vy( float ivn );
void set_ax( float in );
void set_ay( float in );
void set_vx( float in );
void set_vy( float in );
void set_x( float in );
void set_y( float in );
