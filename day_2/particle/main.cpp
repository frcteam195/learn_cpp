#include "particle.hpp"


class CustomEmitter : public Emitter
{
public:
    CustomEmitter( sf::Vector2f pos )
	: Emitter( pos )
    {

	colour = sf::Color::Green;

	std::cout << "asdasdas\n\n\n";
    }
};

int main()
{
    run_particle_system<CustomEmitter>( );
    return 0;
}
