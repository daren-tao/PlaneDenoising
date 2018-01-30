
#include <iostream>
#include <algorithm>
#include "PlyParser.hpp"
#include "Plane.hpp"

void	getRand(float randTab[3])
{
	randTab[0] = rand() % 1000;
	randTab[1] = rand() % 1000;
	randTab[2] = rand() % 1000;
	while (randTab[1] == randTab[0])
		randTab[0] = rand() % 1000;
	while (randTab[2] == randTab[0] && randTab[2] != randTab[1])
		randTab[2] = rand() % 1000;
}

void plane_from_points(std::vector<Vec> points)
{
	int  n = points.size();
	Vec sum;
	for (auto const& value : points)
	{
		sum = sum.add(value);
	}
	Vec centroid = sum.div(n);

	// Calc full 3x3 covariance matrix, excluding symmetries:
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

	Vec dir;
	if (det_max == det_x)
	{
		dir.x = det_x;
		dir.y = xz * yz - xy * zz;
		dir.z = xy * yz - xz * yy;
	}
	else if (det_max == det_x)
	{
		dir.x = xz * yz - xy * zz;
		dir.y = det_y;
		dir.z = xy * xz - yz * xx;
	}
	else
	{
		dir.x = xy * yz - xz * yy;
		dir.y = xy * xz - yz * xx;
		dir.z = det_z;
	}
	//plane_from_point_and_normal(&centroid, &normalize(dir))
}


int main()
{
	PlyParser parser("../ressources/Ply/test10.ply");
	std::vector<Vec> directions;
	Vec total(0, 0, 0);
	srand(time(NULL));
	float minx = 0;
	float maxx = 0;
	float miny = 0;
	float maxy = 0;
	float minz = 0;
	float maxz = 0;
	for (int i = 0; i < 1000; i++)
	{
		if (parser._vectors[i].x < minx)
			minx = parser._vectors[i].x;

		if (parser._vectors[i].y < miny)
			miny = parser._vectors[i].y;

		if (parser._vectors[i].z < minz)
			minz = parser._vectors[i].z;



		if (parser._vectors[i].x > maxx)
			maxx = parser._vectors[i].x;

		if (parser._vectors[i].y > maxy)
			maxy = parser._vectors[i].y;

		if (parser._vectors[i].z > maxz)
			maxz = parser._vectors[i].z;
	}
	float x = maxx - minx;
	float y = maxy - miny;
	float z = maxz - minz;
	//floaz gg = pRef.n.dot(Vec(-0.65266f, -0.864288f, -0.493803f).normalize());
	std::cout << "Bonjour !" << std::endl;
}