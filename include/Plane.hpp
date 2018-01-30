
#ifndef _PLANE_HPP_
#define _PLANE_HPP_


#include "Vector.hpp"

struct Plane
{
	// Plane equation n.dot(X) = d;
	Vec n;
	float d;

	// point in the plane
	Vec p;

	Plane(const Vec& n_, const float& d_, const Vec& p_)
		: n(n_)
		, d(d_)
		, p(p_)
	{}

	Plane(Vec A, Vec B, Vec C)
	{
		if ((B.sub(A)).normalize().dot((C.sub(A)).normalize()) == 1)
			n = Vec(0, 0, 0);
		else
		{
			n = ((B.sub(A)).normalize()).cross((C.sub(A)).normalize());
			n = n.normalize();
		}
		d = n.dot(A);
		p = A;
	}

	bool isOnPlane(Vec& v)
	{
		float res = std::fabs(v.dot(n) - d);
		std::cout << res << std::endl;
		return res < 0.1E-4;
	}

	std::string print(bool pretty = false)
	{
		std::stringstream os;
		if (pretty)
			os << "[" << n.x << ", " << n.y << ", " << n.z << ", " << d << "]";
		else
			os << std::fixed << std::setprecision(2) << n.print() << " " << d;

		return os.str();
	}

	Plane& operator+=(const Plane& plane)
	{
		n = n.add(plane.n);
		d += plane.d;
		p = p.add(plane.p);
		return *this;
	}

	Plane& operator/=(const int &divider)
	{
		n.div(divider);
		d /= divider;
		p.div(divider);
		return *this;
	}

};



#endif // !_PLANE_HPP_
