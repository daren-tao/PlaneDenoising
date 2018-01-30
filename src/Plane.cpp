

#include "Plane.hpp"

Plane::Plane(std::vector<Vec> points)
{
	int  n = points.size();
	Vec sum(0, 0, 0);
	for (auto const& value : points)
	{
		sum = sum.add(value);
	}
	Vec centroid = sum.div(n);

	float xx = 0.0; float xy = 0.0; float xz = 0.0;
	float yy = 0.0; float yz = 0.0; float zz = 0.0;

	Vec r;
	for (auto const& value : points)
	{
		r = value.sub(centroid);
		xx += r.x * r.x;
		xy += r.x * r.y;
		xz += r.x * r.z;
		yy += r.y * r.y;
		yz += r.y * r.z;
		zz += r.z * r.z;
	}

	float det_x = yy * zz - yz * yz;
	float det_y = xx * zz - xz * xz;
	float det_z = xx * yy - xy * xy;

	float det_max = std::max(std::max(det_x, det_y), det_z);

	if (det_max == det_x)
	{
		_n.x = det_x;
		_n.y = xz * yz - xy * zz;
		_n.z = xy * yz - xz * yy;
	}
	else if (det_max == det_x)
	{
		_n.x = xz * yz - xy * zz;
		_n.y = det_y;
		_n.z = xy * xz - yz * xx;
	}
	else
	{
		_n.x = xy * yz - xz * yy;
		_n.y = xy * xz - yz * xx;
		_n.z = det_z;
	}
	_n = _n.normalize();
	_p = centroid;
	_d = -_n.dot(_p);
}
