#include "bounce.hpp"
#include <SFML/Graphics.hpp>

sf::RenderWindow* window;

float x = 0;
float y = 0;
float vx = 0;
float vy = 0;
float ax = 0;
float ay = 0;
float max_vx = 10;
float max_vy = 10;

float circle_radius = 20;

int circle_r = 255;
int circle_g = 0;
int circle_b = 0;

int bg_r = 255;
int bg_g = 255;
int bg_b = 255;

bool is_init = false;
int init_w = 800;
int init_h = 600;

void set_ball_color( int r, int g, int b )
{
    circle_r = r;
    circle_g = g;
    circle_b = b;
}

void set_bg_color( int r, int g, int b )
{
    bg_r = r;
    bg_g = g;
    bg_b = b;
}

float get_x()
{
    return x;
}

float get_y()
{
    return y;
}

float get_vx()
{
    return vx;
}

float get_vy()
{
    return vy;
}

float get_ax()
{
    return ax;
}

float get_ay()
{
    return ay;
}

void set_max_vx( float in )
{
    max_vx = in;
}
void set_max_vy( float in )
{
    max_vy = in;
}

void set_ax( float in )
{
    ax = in;
}
void set_ay( float in )
{
    ay = in;
}

void set_vx( float in )
{
    vx = in;
}

void set_vy( float in )
{
    vy = in;
}

void set_x( float in )
{
    x = in;
}

void set_y( float in )
{
    y = in;
}

float get_r()
{
    return circle_radius;
}

void draw()
{
    window->clear( sf::Color( bg_r, bg_g, bg_b ) );
    sf::CircleShape shape(circle_radius);
    shape.setFillColor(sf::Color(circle_r,
                                 circle_g,

                                 circle_b));

    shape.setPosition( x, y );

    window->draw(shape);

    window->display();
}

float get_window_width()
{
    if( !is_init )
        return init_w;

    return window->getSize().x;
}

float get_window_height()
{
    if( !is_init)
        return init_h;

    return window->getSize().y;
}

void internal_step()
{
    x += vx;
    y += vy;
    vx += ax;
    vy += ay;

    vx = vx > max_vx ? max_vx : vx;
    vy = vy > max_vy ? max_vy : vy;
}

void run()
{
    sf::Clock clock;
    sf::Time accumulator = sf::Time::Zero;
    sf::Time ups = sf::seconds(1.f / 60.0f);

    window = new sf::RenderWindow(sf::VideoMode(init_w, init_h), "Ball Bounce");
    is_init = true;

    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();

            if( event.type == sf::Event::MouseButtonPressed )
            {
                on_mouse_down( event.mouseButton.button,
                               event.mouseButton.x,
                               event.mouseButton.y );
            }
        }

        while (accumulator > ups)
        {
            accumulator -= ups;
            internal_step();
            step();
            draw();
        }

        accumulator += clock.restart();
    }

}
