#ifndef _VECTOR3_H_
#define _VECTOR3_H_
#include <math.h>
template <class TYPE>

class Vector3
{
public:
	TYPE x, y, z;

	Vector3( TYPE _x, TYPE _y, TYPE _z): x(_x), y(_y), z(_z) {}

	//Operators + - += -= == =

	Vector3& operator = (Vector3& entrada)
	{
		x = entrada.x;
		y = entrada.y;
		z = entrada.z;
		return *this;
	}

	bool operator == (Vector3& vec2)const
	{
		if (x == vec2.x && y == vec2.y && z == vec2.z)
			return true;
		return false;
	}

	bool operator != (Vector3& vec2)const
	{
		if (x != vec2.x || y != vec2.y || z != vec2.z)
			return true;
		return false;
	}

	Vector3& operator + (Vector3& vec2)
	{
		x = x + vec2.x;
		y = y + vec2.y;
		z = z + vec2.z;
		return *this;
	}

	Vector3& operator - (Vector3& vec2)
	{
		x = x - vec2.x;
		y = y - vec2.y;
		z = z - vec2.z;
		return *this;
	}

	Vector3& operator += (Vector3& vec2)
	{
		x += vec2.x;
		y += vec2.y;
		z += vec2.z;
		return *this;
	}

	Vector3& operator -= (Vector3& vec2)
	{
		x -= vec2.x;
		y -= vec2.y;
		z -= vec2.z;
		return *this;
	}

	TYPE getModule()
	{
		TYPE result = 0;
		result = pow(x, 2) + pow(y, 2) + pow(z, 2);
		return sqrt(result);
	}
};

#endif