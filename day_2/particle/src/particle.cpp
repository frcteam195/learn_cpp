#include "particle.hpp"

float random_float(const float from, const float to)
{
    unsigned int seed = static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count());
    static std::default_random_engine engine(seed);
    std::uniform_real_distribution<float> dist(from, to);
    return dist(engine);
}

void ParticleSystem::update(const float dt)
{
    for (auto emitter = emitters.begin(); emitter != emitters.end();)
    {
	if (!emitter->permanent)
	{
	    emitter->lifetime -= dt;
	    if (emitter->lifetime <= 0.0f) emitter->alive = false;
	}

	int count = emitter->count;
	for (int i = 0; i < emitter->count; i++)
	{
	    Particle& particle = emitter->particles[i];
	    sf::Vertex& vertex = emitter->vertices[i];

	    particle.lifetime -= dt;
	    if (particle.lifetime <= 0.0f)
	    {
		vertex.position = emitter->position;
		if (emitter->alive)
		{
		    float parangle;
		    if (emitter->directional)
		    {
			parangle = random_float(emitter->angle - emitter->deviation, emitter->angle + emitter->deviation);
		    }
		    else
		    {
			parangle = random_float(0.0f, 360.0f);
		    }
		    particle.velocity.x = static_cast<float>(std::cos(parangle * 0.0174533));
		    particle.velocity.y = static_cast<float>(std::sin(parangle * 0.0174533));
		    particle.velocity *= random_float(1.0f, emitter->velocity);

		    particle.lifetime = random_float(emitter->minlifetime, emitter->maxlifetime);
		    particle.olifetime = particle.lifetime;
		    if (!emitter->explosion)
		    {
			vertex.color = emitter->colour;
		    }
		}
		else
		{
		    vertex.color = sf::Color::Transparent;
		    count--;
		}
	    }

	    vertex.position += particle.velocity * dt;
	    vertex.color.a = static_cast<uint8_t>((particle.lifetime / particle.olifetime) * 255);
	}

	if (!count) emitter = emitters.erase(emitter);
	else emitter++;
    }
}


uint16_t ParticleSystem::add( Emitter in )
{
    emitters.emplace_back(in);
    return ids;
}

void ParticleSystem::remove(const uint16_t uid)
{
    auto it = std::find(emitters.begin(), emitters.end(), uid);
    if (it == emitters.end()) return;
    it->alive = false;
}

void ParticleSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::VertexArray vertices(sf::Points);
    for (auto& emitter : emitters)
    {
	for (unsigned int i = 0; i < emitter.vertices.getVertexCount(); i++)
	{
	    vertices.append(emitter.vertices[i]);
	}
    }
    target.draw(vertices);
}

