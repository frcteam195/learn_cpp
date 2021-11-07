#include "particle.hpp"



Emitter::Emitter( sf::Vector2f pos )
{
    uid = 0;
    count = 100;
    position = pos;
    colour = sf::Color::Red;
    velocity = 50.0;
    minlifetime = 0.5;
    maxlifetime = 2.0;
    explosion = true;
    permanent = true;
    lifetime = 0;
    directional = true;
    angle = 90.0;
    deviation = 20.0;
    particles = std::vector<Particle>(count);
    vertices = sf::VertexArray(sf::Points, count);

    for (auto& particle : particles)
    {
	if (explosion)
	{
	    float parangle;
	    if (directional)
	    {
		parangle = random_float(angle - deviation, angle + deviation);
	    }
	    else
	    {
		parangle = random_float(0.0f, 360.0f);
	    }
	    particle.velocity.x = static_cast<float>(std::cos(parangle * 0.0174533));
	    particle.velocity.y = static_cast<float>(std::sin(parangle * 0.0174533));
	    particle.velocity *= random_float(1.0f, velocity);
	}

	particle.lifetime = random_float(0.0f, maxlifetime);
	particle.olifetime = particle.lifetime;
    }
    for (int i = 0; i < count; i++)
    {
	vertices[i].position = position;
	if (explosion)
	{
	    vertices[i].color = colour;
	}
	else
	{
	    vertices[i].color = sf::Color::Transparent;
	}
    }
}

