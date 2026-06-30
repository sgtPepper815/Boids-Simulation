#include "config.h"
#include "Boid.h"
#include "Flock.h"
#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow m_window(sf::VideoMode({ SCREEN_WIDTH, SCREEN_HEIGHT }), "Boids Simulation");

	m_window.setFramerateLimit(60);

	sf::Clock clock;

	Flock flock;

	sf::ConvexShape shape(3);

	while (m_window.isOpen())
	{
		// delta time
		float dt = clock.restart().asSeconds();
		dt = std::min(dt, 0.0166f);

		while (auto ev = m_window.pollEvent()) {
			
			if (ev->is<sf::Event::Closed>()) m_window.close();
						
			if (auto* kp = ev->getIf<sf::Event::KeyPressed>()) {
				if (kp->scancode == sf::Keyboard::Scancode::Escape) m_window.close();
			}
		}

		m_window.clear(sf::Color::White);
		flock.update(dt);


		for (auto& b: flock.boids)
		{
			b.draw(m_window, b, shape);
		}

		

		m_window.display();
	}

	return 0;
}
