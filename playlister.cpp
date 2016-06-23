#include <iostream>
#include <vector>
#include "tracks.hpp"
#include "tag-lister.hpp"
#include "formattedJSON-parser.hpp"
#include "track-sorter.hpp"

class playlist{
public:
	int n;
	string name;
	vector<track> tracklist;
};

playlist pl;

void cls(){ ///Clears the console screen in a "Cabreiro" way.
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

void generate(){
	int op, i=0;
	char chop;
	cls();
	pl.tracklist.clear();
	tagl::listall();
	cout << "Type desired genre's code: ";
	cin >> op;
	if(op<0 || op>255){
		cout << "Invalid genre.";
	}
	//if(!parsed(op)){
	if(fjson::parse(op, &(pl.tracklist)))
		cout << "\n.json parsed. Which name will you give the playlist?\n>>";
	else return;
	cin >> pl.name;
	cout << endl << "How do you want to sort the tracks?\nr - random\nd - decrescent popularity\nc - crescent popularity" << endl;
	cin >> chop;
	if(chop=='r'){
		random_shuffle(pl.tracklist.begin(), pl.tracklist.end());
	}
	else{
		tsort::heap(&(pl.tracklist), chop);
	}
	cout << "\nHow many tracks do you want on your playlist?\n>>";
	cin >> pl.n;

	int plsize=pl.tracklist.size();
	while(i<pl.n && i<plsize){
		cout << pl.tracklist[i].name << "   " << pl.tracklist[i].popularity << endl;
		cout << "   album: " << pl.tracklist[i].album << endl;
		cout << "   artist: " << pl.tracklist[i].artist[0] << endl;
		i++;
	}

	cout << "\nPress 'Enter' to proceed.";
	getchar();
	getchar();


	//multiple genres?
}

int main(){
	bool exit=false;
	char op;
	cls();
	do{
		cout<< "\t _______________________________\n"
			<< "\t|           playlister          |\n"
			<< "\t+-------------------------------+\n"
			<< "\t|   1.Generate a new playlist   |\n"
			<< "\t|  2.Load an existing playlist  |\n"
			<< "\t| Press 'E' to exit the program |\n"
			<< "\t+-------------------------------+\n\n>>";
		op=cin.get();
		switch(op){
			case '1':
				generate();
				cls();
				break;
			case '2':
				//load playlists
				cls();
				break;
			case 'e':
			case 'E':
				exit=true;
				break;
			default:
				cls();
				cout << "Invalid input.\n\n";
		}
	}while(!exit);
	//fjson::parse(0);
	return 0;
}