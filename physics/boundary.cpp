#include "boundary.h"

BoundaryBox::BoundaryBox(float width, float height, float length) {
	this->width = width;
	this->height = height;
	this->length = length;
};

BoundaryCapsule::BoundaryCapsule(float height, float radius) {
	this->height = height;
	this->radius = radius;
};

BoundaryPlane::BoundaryPlane(float width, float height) {
	this->width = width;
	this->height = height;
};

BoundarySphere::BoundarySphere(float radius) {
	this->radius = radius;
};