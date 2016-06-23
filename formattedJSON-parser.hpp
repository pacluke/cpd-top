#ifndef FORMATTEDJSON_PARSER_HPP
#define FORMATTEDJSON_PARSER_HPP

#include "tracks.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

namespace fjson{
	bool parse(int genre, vector<ramtrack> * tracklist){
		int tracks_read=0, i, pos;
		string strbuf;
		string line, output;
		track trackbuffer;
		ramtrack ramtrackbuffer;

		output = "./Data/Binaries/" + to_string(genre) + ".bin";
		line = "./Data/" + to_string(genre) + ".json";
		
		ifstream file(line, ios::in);
		if(!file.is_open()){
			cout << "Error opening json file." << endl;
			return false;
		}
		
		ofstream file2(output, ios::out | ios::binary);
		if(!file2.is_open()){
			cout << "Error opening output file." << endl;
			file.close();
			return false;
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
			strbuf=line.substr(pos+9, line.find_last_of("\"")-(pos+9));
			copy(strbuf.begin(), strbuf.end(), trackbuffer.album);
			trackbuffer.album[strbuf.size()] = '\0';

			getline(file, line);
			getline(file, line);
			i=0;
			
			do{
				getline(file, line);
				pos=line.find("name");
				if(pos!=-1){
					strbuf=line.substr(pos+9, line.find_last_of("\"")-(pos+9));
					copy(strbuf.begin(), strbuf.end(), trackbuffer.artist[i]);
					trackbuffer.artist[i][strbuf.size()] = '\0';
					i++;
					getline(file, line);
				}
				if(i<4){
					trackbuffer.artist[i][0] = '\0';
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
			strbuf=line.substr(pos+9, line.find_last_of("\"")-(pos+9));
			copy(strbuf.begin(), strbuf.end(), trackbuffer.name);
			trackbuffer.name[strbuf.size()] = '\0';
			getline(file, line);
			pos=line.find("popularity");
			trackbuffer.popularity=stoi(line.substr(pos+14));
			file2.write((char *)&trackbuffer, sizeof(track));
			ramtrackbuffer.popularity=trackbuffer.popularity;
			ramtrackbuffer.offset=tracks_read;
			(*tracklist).push_back(ramtrackbuffer);
			tracks_read++;
		}
		if(tracks_read!=stoi(line.substr(pos+9))){
			cout << "ERROR: json doesn't follow specified syntax." << endl;
			file.close();
			return false;
		}
		file.close();
		file2.close();
		return true;
	}
}


#endif //FORMATTEDJSON_PARSER_HPP