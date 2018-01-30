
#ifndef _PLANE_HPP_
#define _PLANE_HPP_


#include "Vector.hpp"

struct Plane
{
	// Plane equation n.dot(X) = d;
	Vec _n;
	float _d;

	// point in the plane
	Vec _p;

	Plane(const Vec& n_, const float& d_, const Vec& p_)
		: _n(n_)
		, _d(d_)
		, _p(p_)
	{}

	Plane(Vec A, Vec B, Vec C)
	{
		if ((B.sub(A)).normalize().dot((C.sub(A)).normalize()) == 1)
			_n = Vec(0, 0, 0);
		else
		{
			_n = ((B.sub(A)).normalize()).cross((C.sub(A)).normalize());
			_n = _n.normalize();
		}
		_d = _n.dot(A);
		_p = A;
	}

	bool isOnPlane(Vec& v)
	{
		float res = std::fabs(v.dot(_n) - _d);
		std::cout << res << std::endl;
		return res < 0.1E-4;
	}

	std::string print(bool pretty = false)
	{
		std::stringstream os;
		if (pretty)
			os << "[" << _n.x << ", " << _n.y << ", " << _n.z << ", " << _d << "]";
		else
			os << std::fixed << std::setprecision(2) << _n.print() << " " << _d;

		return os.str();
	}

	Plane& operator+=(const Plane& plane)
	{
		_n = _n.add(plane._n);
		_d += plane._d;
		_p = _p.add(plane._p);
		return *this;
	}

	Plane& operator/=(const int &divider)
	{
		_n.div(divider);
		_d /= divider;
		_p.div(divider);
		return *this;
	}

	Plane(std::vector<Vec> points);

};



#endif // !_PLANE_HPP_
