#pragma once

namespace myMath
{
	struct Vector2
	{ float x; float y;
	//Vector2 &operator=(Point rhs);
	};
	struct Point { float x; float y; };
	struct Rectangle { float x; float y; float sizeX; float sizeY; };

	Vector2 operator+(Vector2 lhs, Vector2 rhs) { return{ lhs.x + rhs.x, lhs.y + rhs.y }; }
	Vector2 operator-(Vector2 lhs, Vector2 rhs) { return{ lhs.x - rhs.x, lhs.y - rhs.y }; }
	Vector2 operator*(Vector2 lhs, Vector2 rhs) { return{ lhs.x * rhs.x, lhs.y * rhs.y }; }
	Vector2 operator/(Vector2 lhs, Vector2 rhs) { return{ lhs.x / rhs.x, lhs.y / rhs.y }; }

	Vector2 operator+(Vector2 lhs, Point rhs) { return{ lhs.x + rhs.x, lhs.y + rhs.y }; }
	Vector2 operator-(Vector2 lhs, Point rhs) { return{ lhs.x - rhs.x, lhs.y - rhs.y }; }
	Vector2 operator*(Vector2 lhs, Point rhs) { return{ lhs.x * rhs.x, lhs.y * rhs.y }; }
	Vector2 operator/(Vector2 lhs, Point rhs) { return{ lhs.x / rhs.x, lhs.y / rhs.y }; }
	//Vector2 &Vector2::operator=(Point rhs) { x = rhs.x; y = rhs.y; return *this; } // this->x; (*this).x;

	Vector2 operator+(Point lhs, Point rhs) { return{ lhs.x + rhs.x, lhs.y + rhs.y }; }
	Vector2 operator-(Point lhs, Point rhs) { return{ lhs.x - rhs.x, lhs.y - rhs.y }; }
	Vector2 operator*(Point lhs, Point rhs) { return{ lhs.x * rhs.x, lhs.y * rhs.y }; }
	Vector2 operator/(Point lhs, Point rhs) { return{ lhs.x / rhs.x, lhs.y / rhs.y }; }
}
