# Boids Flocking Simulation
A real-time flocking simulation based on Craig Reynolds' Boids algorithm (1987), built with C++17 and SFML 3.

Boids simulates emergent swarm behaviour through three simple steering rules applied to each agent:


Separation – avoid crowding nearby boids
Alignment – steer towards the average heading of neighbours
Cohesion – steer towards the average position of neighbours


No boid is told to form a flock – the group behaviour emerges entirely from these local rules.

Features


5000+ boids at 60 FPS 

Dynamic colour based on speed 

Spatial hashing grid for O(n) neighbour lookup


Performance

Naive implementation runs O(n²) – every boid checks every other boid. With spatial hashing, each boid only checks its immediate grid neighbours.


![Boids Demo](boids.gif)
