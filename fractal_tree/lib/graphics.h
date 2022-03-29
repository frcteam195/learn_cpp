#include <SFML/Graphics.hpp>

class Graphics
{
public:
    Graphics( int width, int height );
    ~Graphics();

    // window and input ---------------------------
    int get_width();
    int get_height();

    int get_mouse_x();
    int get_mouse_y();

    bool is_L_mouse_down();
    bool is_R_mouse_down();
    bool is_M_mouse_down();

    bool is_L_mouse_clicked();
    bool is_R_mouse_clicked();
    bool is_M_mouse_clicked();

    bool is_running();
    void clear();
    void draw();

    // drawing ------------------------------------

    // line
    void line( float x1, float y1,
	       float x2, float y2 );

    void line( float x1, float y1,
	       float x2, float y2,
	       int r, int g, int b, int a);

    // circle
    void circle( float x, float y, float radius );

    void circle( float x, float y, float radius,
		 int r, int g, int b, int a,
		 bool is_outline );

    // rectangle
    void rect( float x, float y,
	       float w, float h );

    void rect( float x, float y,
	       float w, float h,
	       float angle,
	       int r, int g, int b, int a,
	       bool is_outline );


    sf::Color clear_color;

private:
    int _width;
    int _height;
    int _mouse_x;
    int _mouse_y;
    sf::RenderWindow* window;
    sf::Clock clock;
    sf::Time accumulator;
    sf::Time ups;

    bool _l_mouse_down;
    bool _r_mouse_down;
    bool _m_mouse_down;

    bool _l_click_signal;
    bool _r_click_signal;
    bool _m_click_signal;
};
