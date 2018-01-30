

#ifndef _VECTOR_HPP_
#define _VECTOR_HPP_

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <string>

struct Vec
{
	float x;
	float y;
	float z;

	Vec(const float& a, const float& b, const float& c)
		: x(a)
		, y(b)
		, z(c)
	{}

	Vec(const Vec& v)
		: x(v.x)
		, y(v.y)
		, z(v.z)
	{}

	Vec() {}

	float dot(const Vec& other)
	{
		return x * other.x + y * other.y + z * other.z;
	}

	Vec cross(const Vec& other)
	{
		return Vec((y * other.z) - (z * other.y),
			(z * other.x) - (x * other.z),
			(x * other.y) - (y * other.x));
	}

	float norm() { return sqrt(dot(*this)); }

	Vec normalize() { return Vec(x / norm(), y / norm(), z / norm()); }

	std::string print(bool pretty = false)
	{
		std::stringstream os;
		if (pretty)
			os << "[" << x << ", " << y << ", " << z << "]";
		else
			os << std::fixed << std::setprecision(2) << x << " " << y << " " << z;

		return os.str();
	}

	Vec getPerpendicular()
	{
		std::vector<float> vec{ x, y, z };
		auto min = std::min_element(vec.begin(), vec.end()) - vec.begin();

		return Vec(0, vec[(min + 2) % 3], -vec[(min + 1) % 3]);
	}

	Vec scale(const float& s) { return Vec(x * s, y * s, z * s); }
	Vec sub(const Vec& v) const { return Vec(x - v.x, y - v.y, z - v.z); }
	Vec add(const Vec& v) { return Vec(x + v.x, y + v.y, z + v.z); }
	Vec div(const int& d) { return Vec(x / (float)d, y / (float)d, z / (float)d); }
	Vec mult(const int& d) { return Vec(x * (float)d, y * (float)d, z * (float)d); }
};

#endif // !_VECTOR_HPP_
