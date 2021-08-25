#include "Object.h"
#include "Constants.h"

Object::Object(sf::Vector2f &pos, sf::Vector2f &size) {
	setPosition(pos);
	setSize(size);
};
Object::~Object() {};

void Object::updatePos(float deltatime) {
	float accelX = -getVelocity().x * (1 - FRICTION) * deltatime;
	float accelY = -getVelocity().y * (1 - FRICTION) * deltatime + GRAVITY * deltatime;
	setVelocity(sf::Vector2f(getVelocity().x + accelX, getVelocity().y + accelY));
	move(velocity);
}

void Object::setVelocity(sf::Vector2f v) {
	this->velocity = v;
}

sf::Vector2f Object::getVelocity() {
	return velocity;
}
