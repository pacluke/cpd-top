#ifndef FORMATTEDJSON_PARSER_HPP
#define FORMATTEDJSON_PARSER_HPP

#include "tracks.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

namespace fjson{
	bool parse(int genre, vector<track> * tracklist){
		int tracks_read=0, i, pos;
		string line;
		track trackbuffer;

		line = "./Data/" + to_string(genre) + ".json";
		ifstream file;
		
		file.open(line, ifstream::in);
		if(!file.is_open()){
			cout << "Error opening json file." << endl;
		}
		

		while(1){
			getline(file, line);
			getline(file, line);
			getline(file, line);
			pos=line.find("total");
			if(pos!=-1){
				break;
			}
			getline(file, line);
			getline(file, line);
			pos=line.find("name");
			trackbuffer.album=line.substr(pos+9, line.find_last_of("\"")-(pos+9));

			getline(file, line);
			getline(file, line);
			i=0;
			
			do{
				getline(file, line);
				pos=line.find("name");
				if(pos!=-1){
					trackbuffer.artist[i]=line.substr(pos+9, line.find_last_of("\"")-(pos+9));
					i++;
					getline(file, line);
				}
			}while(pos!=-1);

			pos=line.find("duration_ms");
			trackbuffer.duration_ms=stoi(line.substr(pos+15, line.find_last_of(",")-(pos+15)));
			getline(file, line);
			if((int)line.find("false")!=-1)
				trackbuffer.isexplicit=false;
			else
				trackbuffer.isexplicit=true;
			getline(file, line);
			pos=line.find("name");
			trackbuffer.name=line.substr(pos+9, line.find_last_of("\"")-(pos+9));
			getline(file, line);
			pos=line.find("popularity");
			trackbuffer.popularity=stoi(line.substr(pos+14));
			(*tracklist).push_back(trackbuffer);
			tracks_read++;
		}
		if(tracks_read!=stoi(line.substr(pos+9))){
			cout << "ERROR: json doesn't follow specified syntax." << endl;
			file.close();
			return false;
		}
		file.close();
		return true;
	}
}


#endif //FORMATTEDJSON_PARSER_HPP