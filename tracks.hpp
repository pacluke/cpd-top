#ifndef TRACKS_HPP
#define TRACKS_HPP

#include <string>

class track{
public:
	char album[256];
	char artist[4][256];
	int duration_ms;
	bool isexplicit;
	char name[256];
	int popularity;
};

class ramtrack{
public:
	int offset;
	int popularity;
};

#endif //TRACKS_HPP