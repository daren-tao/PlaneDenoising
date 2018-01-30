
#ifndef _PLYPARSER_HPP_
#define _PLYPARSER_HPP_

#include <queue>
#include <map>
#include <fstream>

#include "Vector.hpp"

typedef enum e_plyFormat {
	Ascii,
	BigEndian,
	LittleEndian,
} PlyFormat;

const std::map<PlyFormat, std::string> formatMap = {
	{ Ascii, "ascii 1.0" },
	{ BigEndian, "binary_big_endian 1.0" },
	{ LittleEndian, "binary_little_endian 1.0" },
};


class PlyParser
{
private:
	PlyFormat plyFormat;
	std::queue<std::string> comments;
	std::queue<std::string> properties;
	int vertexNumber;

public:
	std::fstream _fs;
	std::vector<Vec> _vectors;


public:
	PlyParser(const std::string &fileName);
	~PlyParser();

private:
	void parseHeader();
	void parseBody();

};

#endif // !_PLYPARSER_HPP_
