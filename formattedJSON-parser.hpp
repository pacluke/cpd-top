#ifndef FORMATTEDJSON_PARSER_HPP
#define FORMATTEDJSON_PARSER_HPP

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

namespace fjson{
	class track{
	public:
		string album;
		string artist[5];
		int duration_ms;
		bool isexplicit;
		string name;
		int popularity;
	};
	void parse(int genre){
		int tracks_read=0, i, pos;
		track tracklist;
		string line;

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
			tracklist.album=line.substr(pos+9, line.find_last_of("\"")-(pos+9));

			getline(file, line);
			getline(file, line);
			i=0;
			
			do{
				getline(file, line);
				pos=line.find("name");
				if(pos!=-1){
					tracklist.artist[i]=line.substr(pos+9, line.find_last_of("\"")-(pos+9));
					i++;
					getline(file, line);
				}
			}while(pos!=-1);

			pos=line.find("duration_ms");
			tracklist.duration_ms=stoi(line.substr(pos+15, line.find_last_of(",")-(pos+15)));
			getline(file, line);
			if((int)line.find("false")!=-1)
				tracklist.isexplicit=false;
			else
				tracklist.isexplicit=true;
			getline(file, line);
			pos=line.find("name");
			tracklist.name=line.substr(pos+9, line.find_last_of("\"")-(pos+9));
			getline(file, line);
			pos=line.find("popularity");
			tracklist.popularity=stoi(line.substr(pos+14));
			tracks_read++;
		}
		if(tracks_read!=stoi(line.substr(pos+9))){
			cout << "ERROR: json doesn't follow specified syntax." << endl;
		}
		else{
			cout << "json file successfully parsed and converted to tree." << endl;
		}
		file.close();
	}
}


#endif //FORMATTEDJSON_PARSER_HPP