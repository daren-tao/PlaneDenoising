
#include <iostream>
#include <algorithm>
#include "PlyParser.hpp"
#include "Plane.hpp"

#include <sys/stat.h>

void	writePointsToPlane(const std::vector<Vec>& points, const std::string& filename, const PlyParser &parser)
{
	const size_t numPoints(points.size());
	std::stringstream ss;
	ss << "ply" << std::endl
		<< "format " << formatMap.at(parser.plyFormat) << std::endl
		<< "comment" << parser.comments.front() << " & Adrien Bedel"<< std::endl
		<< "element vertex " << numPoints << std::endl
		<< "property" << parser.properties[0] << std::endl
		<< "property" << parser.properties[1] << std::endl
		<< "property" << parser.properties[2] << std::endl
		<< "end_header" << std::endl;
	for (auto point : points)
		ss << point.print() << std::endl;

	std::ofstream out(filename, std::ofstream::out);
	out << ss.str();
	out.close();
}

inline bool existsTest(const std::string& name)
{
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}

int errorCheck(int argc, char* argv[])
{
	if (argc != 4)
	{
		std::cerr << "usage ./denoising path filename nbPointPerPlane" << std::endl;
		std::cerr << "exemple : ./denoising ../ressources/Ply/ test.ply 1000" << std::endl;
		return EXIT_FAILURE;
	}
	std::string path(argv[1]);
	std::string fileName(argv[2]);
	std::string outputFile("projected" + fileName);
	if (existsTest(path + fileName) == false || existsTest(outputFile) == true)
	{
		std::cerr << path << fileName << " doesn't exists or "
			<<	outputFile << " already exists" << std::endl;
		return EXIT_FAILURE;
	}
}

int main(int argc, char* argv[])
{
	if (errorCheck(argc, argv) == 1)
		return (EXIT_FAILURE);

	PlyParser parser(std::string(argv[1]) + std::string(argv[2]), atoi(argv[3]));
	std::vector<Plane> planes;

	Vec origin;
	float dist;
	std::vector<Vec>	projectedPoints;

	for (auto const& vector : parser._vectors)
	{
		planes.push_back(Plane(vector));
	}

	for (int i = 0; i < planes.size(); i++)
	{
		for (auto const& point : parser._vectors[i])
		{
			origin = point.sub(planes[i]._p);
			dist = origin.dot(planes[i]._p);
			projectedPoints.push_back(Vec(point.sub(planes[i]._n.mult(dist))));
		}
	}
	writePointsToPlane(projectedPoints, std::string("projected") + std::string(argv[2]), parser);
	return (0);
}