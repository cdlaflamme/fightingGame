//VectorMath.cpp
//contains functions used in vector math
#include <cmath>

float magnitude (const sf::Vector2f &vect){
	return hypot(vect.x, vect.y);
}

sf::Vector2f normalize(const sf::Vector2f &vector){
	return vector/magnitude(vector);
}

sf::Vector2f project(const sf::Vector2f &A, const sf::Vector2f &B){
	//returns the component of A parallel to B
	return normalize(B) * ((A.x * B.x) + (A.y * B.y));
}

