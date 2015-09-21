#pragma once

#include "MyMath.h"
#include <cmath>

using namespace myMath;
namespace str
{
	struct MapSegment
	{
		Point p1;
		Point p2;
	public:
		MapSegment(Point a, Point b)
		{
			p1 = a;
			p2 = b;
		}
	public:
		Vector2 GetVector()
		{
			return Vector2{ p2.x - p1.x, p2.y - p1.y };
		}
	public:
		Rectangle CollisionRect()
		{
			return Rectangle{ fmin(p1.x, p2.x), fmin(p1.y, p2.y), abs(p1.x - p2.x), abs(p1.y - p2.y) };
		}
	};
	struct Line2D
	{
		Vector2 P;
		Vector2 V;

	public:
		float yInt()
		{
			return (-V.y * P.x + V.x * P.y) / V.x;
		}
	public:
		float Slope()
		{
			return V.y / V.x;
		}
	};
	struct Circle
	{
		Vector2 P;
		double R;

	public:
		Circle(Vector2 p, double r)
		{
			P = p;
			R = r;
		}
	};
	static float Magnitude(Vector2 v)
	{
		return (float)sqrt(v.x * v.x + v.y * v.y);
	}
	static Vector2 VectorNormal(Vector2 v)	// perpendicular function, CCW,
	{
		return Vector2{ -v.y, v.x };
	}
	static Vector2 UnitVector(Vector2 v) // normalization
	{
		return Vector2{ v.x / (float)Magnitude(v), v.y / (float)Magnitude(v) };
	}
	static float DotProduct(Vector2 u, Vector2 v)
	{
		return u.x * v.x + u.y * v.y;
	}
	static Vector2 ReflectedVector(Vector2 v, Vector2 a)
	{
		Vector2 n = VectorNormal(a);

		float co = -2 * (DotProduct(v, n) / (Magnitude(n) * Magnitude(n)));
		Vector2 r;
		r.x = v.x + co * n.x;
		r.y = v.y + co * n.y;
		return r;
	}
	static bool mapSegCol(MapSegment plane, MapSegment seg)
	{
		Vector2 N = VectorNormal(UnitVector(plane.p1 - plane.p2));
		bool r1 = DotProduct(N, seg.p1 - plane.p2) < 0;
		bool r2 = DotProduct(N, seg.p2 - plane.p2) < 0;

		return r1 != r2;
	}
	static bool mapCirSegCol(Circle c, MapSegment mapSeg)
	{
		Vector2 N = VectorNormal(UnitVector(mapSeg.p2 - mapSeg.p1));

		bool r = abs(DotProduct(N, c.P - mapSeg.p2)) <= c.R;

		return r;

	}
}
