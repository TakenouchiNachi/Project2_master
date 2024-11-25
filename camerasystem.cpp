#include"camerasystem.h"

Vector2 MakeCenterOfGravity(Vector2 A, Vector2 B, Vector2 C) {
	Vector2 g;
	g.x = (A.x + B.x + C.x) / 3.0f;
	g.y = (A.y + B.y + C.y) / 3.0f;
	return g;
}