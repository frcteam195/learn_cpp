#include "graphics.h"
#include <iostream>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <thread>

using namespace std;
using namespace std::chrono;

auto next_frame = std::chrono::steady_clock::now();

Graphics::Graphics( int width, int height )
{
    _width = width;
    _height = height;

    window = new sf::RenderWindow(sf::VideoMode(_width, _height), "Main Window");
    clear_color = sf::Color( 255, 255, 255 );

    _l_click_signal = false;
    _r_click_signal = false;
    _m_click_signal = false;


    _l_mouse_down = false;
    _r_mouse_down = false;
    _m_mouse_down = false;

    accumulator = sf::Time::Zero;
    ups = sf::seconds(1.f / 60.0f);
}

Graphics::~Graphics()
{
    delete window;
}

bool Graphics::is_running()
{
    return window->isOpen();
}

void Graphics::line( float x1, float y1,
		     float x2, float y2 )
{
    line( x1, y1,
	  x2, y2,
	  0, 0, 0, 255);
}

void Graphics::line( float x1, float y1,
		     float x2, float y2,
		     int r, int g, int b, int a)
{

    sf::Color c(r,g,b,a);
    sf::Vertex line[] = {
	sf::Vertex(sf::Vector2f(x1, y1), c),
	sf::Vertex(sf::Vector2f(x2, y2), c)
    };

    window->draw( line, 2, sf::Lines );
}

void Graphics::circle( float x, float y, float radius )
{
    circle( x, y, radius,
	    255, 0, 0, 255,
	    false);
}

void Graphics::circle( float x, float y, float radius,
		       int r, int g, int b, int a,
		       bool is_outline )
{

    sf::CircleShape shape(radius);
    if( !is_outline )
    {
	shape.setFillColor(sf::Color(r, g, b, a));
    }
    else
    {
	shape.setFillColor(sf::Color(0, 0, 0, 0));
	shape.setOutlineColor(sf::Color(r, g, b, a));
	shape.setOutlineThickness(3);
    }

    shape.setPosition( x - radius, y - radius );
    window->draw(shape);
}

void Graphics::rect( float x, float y,
		     float w, float h )
{
    rect( x, y,
	  w, h,
	  0,
	  0, 0, 0, 255,
	  false);
}

void Graphics::rect( float x, float y,
		     float w, float h,
		     float angle,
		     int r, int g, int b, int a,
		     bool is_outline )
{

    sf::RectangleShape shape(sf::Vector2f(w, h));
    if( !is_outline )
    {
	shape.setFillColor(sf::Color(r, g, b, a));
    }
    else
    {
	shape.setFillColor(sf::Color(0, 0, 0, 0));
	shape.setOutlineColor(sf::Color(r, g, b, a));
	shape.setOutlineThickness(3);
    }


    shape.setPosition( x, y );
    shape.setOrigin(w/2, h/2);
    shape.setRotation( angle );

    window->draw(shape);

}



void Graphics::draw()
{
    next_frame += std::chrono::milliseconds(1000 / 60); // 5Hz

    sf::Event event;
    while (window->pollEvent(event))
    {
	if (event.type == sf::Event::Closed)
	{
	    window->close();
	}

	if( event.type == sf::Event::MouseButtonPressed )
	{
	    if( event.mouseButton.button == 0 )
	    {
		_l_mouse_down = true;
	    }
	    else if( event.mouseButton.button == 1 )
	    {
		_r_mouse_down = true;
	    }
	    else if( event.mouseButton.button == 2 )
	    {
		_m_mouse_down = true;
	    }

	    _mouse_x = event.mouseButton.x;
	    _mouse_y = event.mouseButton.y;
	}

	if( event.type == sf::Event::MouseButtonReleased )
	{
	    if( event.mouseButton.button == 0 )
	    {
		_l_mouse_down = false;
		_l_click_signal = true;
	    }
	    else if( event.mouseButton.button == 1 )
	    {
		_r_mouse_down = false;
		_r_click_signal = true;
	    }
	    else if( event.mouseButton.button == 2 )
	    {
		_m_mouse_down = false;
		_m_click_signal = true;
	    }

	    _mouse_x = event.mouseButton.x;
	    _mouse_y = event.mouseButton.y;
	}

	if( event.type == sf::Event::MouseMoved )
	{
	    _mouse_x = event.mouseMove.x;
	    _mouse_y = event.mouseMove.y;
	}
    }

    window->display();

    std::this_thread::sleep_until(next_frame);
}

void Graphics::clear()
{
    window->clear( clear_color );
}

int Graphics::get_width()
{
    return _width;
}

int Graphics::get_height()
{
    return _height;
}

int Graphics::get_mouse_x()
{
    return _mouse_x;
}

int Graphics::get_mouse_y()
{
    return _mouse_y;
}


bool Graphics::is_L_mouse_down()
{
    return _l_mouse_down;
}

bool Graphics::is_R_mouse_down()
{
    return _r_mouse_down;
}

bool Graphics::is_M_mouse_down()
{
    return _m_mouse_down;
}


bool Graphics::is_L_mouse_clicked()
{
    if( _l_click_signal )
    {
	_l_click_signal = false;
	return true;
    }
    return false;
}

bool Graphics::is_R_mouse_clicked()
{
    if( _r_click_signal )
    {
	_r_click_signal = false;
	return true;
    }
    return false;
}

bool Graphics::is_M_mouse_clicked()
{
    if( _m_click_signal )
    {
	_m_click_signal = false;
	return true;
    }
    return false;
}

