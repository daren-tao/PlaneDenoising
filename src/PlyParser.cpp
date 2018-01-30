#include "PlyParser.hpp"

PlyParser::PlyParser(const std::string &fileName, int nbPointPerPlane)
{
	_fs = std::fstream(fileName);
	_nbPointsPerPlane = nbPointPerPlane;
	parseHeader();
	parseBody();
}

PlyParser::~PlyParser()
{

}

void PlyParser::parseHeader()
{
	std::string line;
	bool isVertex = false;

	while (std::getline(_fs, line)) {
		std::istringstream stream(line);
		std::string first, rest;
		stream >> first;
		std::getline(stream, rest);
		if (first == "comment")
			comments.push(rest);
		else if (first == "format")
			plyFormat = (rest.substr(1, 20) == "binary_little_endian" ? LittleEndian :
				rest.substr(1, 17) == "binary_big_endian" ? BigEndian : Ascii);
		else if (first == "element") {
			if (rest.substr(1, 6) == "vertex") {
				isVertex = true;
				vertexNumber = std::stoi(rest.substr(7));
			}
			else
				isVertex = false;
		}
		else if (isVertex && first == "property") {
			properties.push_back(rest);
		}
		else if (first == "end_header")
			break;
	}
}

void PlyParser::parseBody()
{
	std::string line;
	std::string floatArray[3];
	std::vector<Vec> tmp;
	while (std::getline(_fs, line))
	{
		int i = 0;
		std::stringstream ssin(line);
		for (int i = 0; ssin.good() && i < 3; i++)
			ssin >> floatArray[i];
		tmp.push_back(Vec(std::strtof(floatArray[0].c_str(), NULL), std::strtof(floatArray[1].c_str(), NULL), std::strtof(floatArray[2].c_str(), NULL)));
		if (tmp.size() == _nbPointsPerPlane)
		{
			_vectors.push_back(tmp);
			tmp.clear();
		}

	}
}
