#ifndef BALL_H
#define	BALL_H

/// @brief Represents a ball in the physics simulation
struct Ball
{
	float x, y;                 /// meters
	float radius;               /// meters
	float velocityX, velocityY; /// m/s
	float mass;                 /// kg
	float restitution;          /// Ranges between 0.0 (perfectly inelastic) - 1.0 (perfectly elastic)
};



#endif // !BALL_H
