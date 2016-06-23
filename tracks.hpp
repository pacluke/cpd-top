#ifndef TRACKS_HPP
#define TRACKS_HPP

#include <string>

class track{
public:
	std::string album;
	std::string artist[4];
	int duration_ms;
	bool isexplicit;
	std::string name;
	int popularity;
};

#endif //TRACKS_HPP