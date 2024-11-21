#include "rope.h"

//Vector2 Lerp(const Vector2* p0, const Vector2* p1, float t) {
//	Vector2 result = {};
//	result.x = p0->x * (1 - t) + p1->x * t;
//	result.y = p0->y * (1 - t) + p1->y * t;
//	return result;
//}
//
//Vector2 Bezier(const Vector2* p0, const Vector2* p1, const Vector2* p2, float t) {
//	Vector2 p0p1 = Lerp(p0, p1, t);
//	Vector2 p1p2 = Lerp(p1, p2, t);
//	Vector2 p = Lerp(&p0p1, &p1p2, t);
//	return p;
//}

Vector2 Lerp(Vector2* p0, Vector2* p1, float t) {
	Vector2 result = {};
	result.x = p0->x * (1 - t) + p1->x * t;
	result.y = p0->y * (1 - t) + p1->y * t;
	return result;
}

Vector2 Bezier(Vector2* p0, Vector2* p1, Vector2* p2, float t) {
	Vector2 p0p1 = Lerp(p0, p1, t);
	Vector2 p1p2 = Lerp(p1, p2, t);
	Vector2 p = Lerp(&p0p1, &p1p2, t);
	return p;
}