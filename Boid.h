#pragma once
#include "config.h"
#include <SFML/Graphics.hpp>
#include <random>

// Helper function to multiply sf::Vector2f by a scalar (float)
inline sf::Vector2f operator*(const sf::Vector2f& v, float s)
{
	return sf::Vector2f(v.x * s, v.y * s);
}

// Helper function to multiply a scalar (float) by sf::Vector2f
inline sf::Vector2f operator*(float s, const sf::Vector2f& v)
{
	return sf::Vector2f(v.x * s, v.y * s);
}

static float len(sf::Vector2f vector) { return sqrt(vector.x * vector.x + vector.y * vector.y); };
static float len2(sf::Vector2f vector) { return (vector.x * vector.x + vector.y * vector.y); };
static sf::Vector2f norm(sf::Vector2f vector) { float l = len(vector); return l > 0 ? vector / l : sf::Vector2f{0,0}; };
static sf::Vector2f clamp(sf::Vector2f vector, float m) { float l = len(vector); return l > m ? norm(vector) * m : vector; };

struct Boid
{
	sf::Vector2f pos;
	sf::Vector2f vel;

	Boid()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> rndW(0, SCREEN_WIDTH);
		std::uniform_int_distribution<> rndH(0, SCREEN_HEIGHT);
		std::uniform_int_distribution<> rndAngle(0, 2*PI);
		std::uniform_int_distribution<> rndVel(1, 120);

		pos = { (float)rndW(gen), (float)rndH(gen) };
		float a = (float)rndAngle(gen);
		float s = (float)rndVel(gen);
		vel = { cos(a) * s, sin(a) * s };
		

	}

	void draw(sf::RenderTarget& rt, Boid& b, sf::ConvexShape& shape)
	{
		float angle = atan2(b.vel.y, b.vel.x);
		float c = cos(angle);
		float s = sin(angle);
		auto rot = [&](float x, float y)->sf::Vector2f {
			return { b.pos.x + c * x - s * y, b.pos.y + s * x + c * y };
			};
		shape.setPoint(0, rot(BOID_SIZE * 2.f, 0));
		shape.setPoint(1, rot(-BOID_SIZE, BOID_SIZE));
		shape.setPoint(2, rot(-BOID_SIZE, -BOID_SIZE));
		shape.setFillColor(b.color());
		rt.draw(shape);
	}
	
	sf::Color color()
	{
		float t = std::min(len(vel) / MAX_SPEED, 1.f);
		return { uint8_t(120 + 140 * t), uint8_t(180 * t), uint8_t(220 - 180 * t), 230 };
	}

	void wrap() {
		if (pos.x < 0)
			pos.x = float(SCREEN_WIDTH) + BOID_SIZE;
		if (pos.x > float(SCREEN_WIDTH) + BOID_SIZE) 
			pos.x = 0;
		if (pos.y < 0)           
			pos.y = float(SCREEN_HEIGHT) + BOID_SIZE;
		if (pos.y > float(SCREEN_HEIGHT) + BOID_SIZE) 
			pos.y = 0;
	}

	sf::Vector2f steer(sf::Vector2f desired)
	{
		return clamp(norm(desired) * MAX_SPEED - vel, MAX_FORCE);
	}

};

