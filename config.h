#pragma once

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 400;
constexpr double PI = 3.1415926535;
constexpr int NUM_BOIDS = 5000;
constexpr int BOID_SIZE = 2;
constexpr float MAX_SPEED = 250.f;

constexpr float COHESION_RADIUS = 80.f;
constexpr float ALIGNMENT_RADIUS = 60.f;
constexpr float SEPARATION_RADIUS = 28.f;

constexpr float MAX_FORCE = 260.f;

constexpr float SEPARATION_WEIGHT = 1.6f;
constexpr float ALIGNMENT_WEIGHT = 1.0f;
constexpr float COHESION_WEIGHT = 0.9f;