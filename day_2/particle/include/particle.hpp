#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include <SFML/Graphics.hpp>
#include <chrono>
#include <random>
#include <iostream>

float random_float(const float from, const float to);

struct Particle
{
    sf::Vector2f velocity;
    float olifetime;
    float lifetime;
};

class Emitter
{
public:
    Emitter(sf::Vector2f pos);

    bool operator==(const uint16_t rhs) { return uid == rhs; }

    uint16_t uid;
    int count;
    std::vector<Particle> particles;
    sf::VertexArray vertices;
    sf::Vector2f position;
    sf::Color colour;
    float velocity;
    float minlifetime;
    float maxlifetime;
    bool explosion;
    bool permanent;
    float lifetime;
    bool directional;
    float angle;
    float deviation;
    bool alive = true;
};



class ParticleSystem : public sf::Drawable
{
public:
    void update(const float dt);
    uint16_t add(Emitter in);
    void remove(const uint16_t uid);

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    uint16_t ids;
    std::vector<Emitter> emitters;
};

template <typename T>
int run_particle_system( ){

    sf::RenderWindow window(sf::VideoMode(640, 480), "Particles");
    window.setFramerateLimit(60);

    sf::Clock clock;
    float dt;

    ParticleSystem particles;
    static int ids = 0;

    sf::Event event;
    while (window.isOpen())
    {
        dt = clock.restart().asSeconds();

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
		    Emitter blank = Emitter(
			window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y))
			);
		    //blank.position = window.mapPixelToCoords( sf::Vector2i(event.mouseButton.x, event.mouseButton.y) );
                    particles.add(blank);
                }
                else if (event.mouseButton.button == sf::Mouse::Right)
                {
		    T custom = T(
			window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y))
			);
                    particles.add(custom);
                }
            }
        }

        particles.update(dt);

        window.clear();
        window.draw(particles);
        window.display();
    }
}


#endif
