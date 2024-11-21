#pragma once
#include "structuer.h"

//Vector2 Lerp(const Vector2* p0, const Vector2* p1, float t);
//
//Vector2 Bezier(const Vector2* p0, const Vector2* p1, const Vector2* p2, float t);

Vector2 Lerp(Vector2* p0, Vector2* p1, float t);

Vector2 Bezier(Vector2* p0, Vector2* p1, Vector2* p2, float t);