#pragma once
#include <vector>
#include "Boid.h"
#include "Grid.h"

struct Flock
{
	std::array<Boid, NUM_BOIDS> boids;

	void update(float delta_time)
	{
		SpatialGrid grid;
		grid.build(boids);

		for (auto& b : boids)
		{
			sf::Vector2f separation;
			sf::Vector2f cohesion;
			sf::Vector2f alignment;

			int s = 0, c = 0, a = 0;


			for (int idx : grid.query(b.pos.x, b.pos.y))
			{
				auto& o = boids[idx];
				if (&o == &b)
					continue;

				// distance
				sf::Vector2f d = b.pos - o.pos;
				float dist2 = len2(d); // no sqrt

				if (dist2 < COHESION_RADIUS * COHESION_RADIUS)
				{
					cohesion += o.pos;
					c++;

					if (dist2 < ALIGNMENT_RADIUS * ALIGNMENT_RADIUS)
					{
						alignment += o.vel;
						a++;

						if (dist2 < SEPARATION_RADIUS * SEPARATION_RADIUS && dist2 > 0)
						{
							float dist = sqrt(dist2);
							separation += d / (dist * dist);
							s++;
						}

					}

				}

			}

			sf::Vector2f _n{};
			if (s > 0) _n += b.steer(separation) * SEPARATION_WEIGHT;
			if (a > 0) { alignment /= (float)a; _n += b.steer(alignment) * ALIGNMENT_WEIGHT; };
			if (c > 0) { cohesion /= (float)c; _n += b.steer(cohesion - b.pos) * COHESION_WEIGHT; };

			b.vel = clamp(b.vel + _n * delta_time, MAX_SPEED);
			b.pos += b.vel * delta_time;
			b.wrap();

		}

	}

};

