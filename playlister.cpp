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
	vector<ramtrack> tracklist;
};

playlist pl;

void cls(){ ///Clears the console screen in a "Cabreiro" way.
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

bool file_exist(string fileName){
    ifstream infile(fileName);
    return infile.good();
}

void build_db(int op, string ind){
	int i;
	ramtrack writebuffer;

	fjson::parse(op, &(pl.tracklist));
	
	tsort::heap(&(pl.tracklist), 'd');
	int plsize=pl.tracklist.size();

	ofstream index(ind, ios::out | ios::binary);
	if(!index.is_open()){
		cout << "Error opening output file." << endl;
		return;
	}
	for(i=0; i<plsize; i++){
		writebuffer.offset=pl.tracklist[i].offset;
		writebuffer.popularity=pl.tracklist[i].popularity;
		index.write((char *)&writebuffer, sizeof(ramtrack));
	}
	index.close();
	pl.tracklist.clear();
}

void generate(){
	int op, i=0;
	char chop;
	string ind;
	ramtrack buffer;

	cls();
	pl.tracklist.clear();
	tagl::listall();
	cout << "Type desired genre's code: ";
	cin >> op;
	if(op<0 || op>255){
		cout << "Invalid genre.";
	}

	ind="./Data/Binaries/index-" + to_string(op) + ".bin";
	if(!file_exist(ind)){
		build_db(op, ind);
	}
	ifstream index(ind, ios::in);
	if(!index.is_open()){
		cout << "Error opening index file." << endl;
		return;
	}
	while(index.good()){
		index.read((char *)&buffer, sizeof(ramtrack));
		pl.tracklist.push_back(buffer);
	}
	pl.tracklist.pop_back();
	index.close();

	cout << "\nWhich name will you give the playlist?\n>>";
	cin >> pl.name;

	cout << endl << "How do you want to sort the tracks?\nr - random\nd - decrescent popularity\nc - crescent popularity" << endl;
	cin >> chop;
	if(chop=='r'){
		random_shuffle(pl.tracklist.begin(), pl.tracklist.end());
	}
	else if(chop=='c'){
		tsort::heap(&(pl.tracklist), chop);
	}
	cout << "\nHow many tracks do you want on your playlist?\n>>";
	cin >> pl.n;

	int plsize=pl.tracklist.size();
	i=0;
	
	string strnewpl = "./Data/Binaries/Playlists/" + tagl::getid3(op) + "_" + pl.name + ".bin";
	ofstream newpl(strnewpl, ios::out | ios::binary);
	if(!newpl.is_open()){
		cout << "Error opening output file." << endl;
		return;
	}
	string filename = "./Data/Binaries/" + to_string(op) + ".bin";
	ifstream file(filename, ios::in | ios::binary);
	if(!file.is_open()){
		cout << "Error opening input file." << endl;
		return;
	}
	track x;
	int intbuf, j=0;
	while(i<pl.n && i<plsize){
		file.seekg(pl.tracklist[i].offset*sizeof(track), file.beg);
		file.read((char *)&x, sizeof(track));
		cout << x.name << " - " << x.popularity << "\n   " << x.album << endl;
		j=0;
		while(x.artist[j][0] && j<4){
			cout << "      " << x.artist[j] << endl;
			j++;
		}
		cout << endl;
		intbuf=pl.tracklist[i].offset;
		newpl.write((char *)&intbuf, sizeof(int));
		i++;
	}
	file.close();
	newpl.close();

	cout << "\nPress 'Enter' to proceed.";
	getchar();
	getchar();
}

void load(){
	string play, sbuf;
	int buffer;
	vector<int> plist;
	cls();
	cout << "Type the playlist's name: ";
	cin >> sbuf;
	getchar();
	play="./Data/Binaries/Playlists/" + sbuf + ".bin";
	ifstream loaded;
	loaded.open(play, ios::in | ios::binary);
	if(!loaded.is_open()){
		cout << "Error loading playlist " << play;
		getchar();
		return;
	}
	int k=0;
	while(loaded.good()){
		loaded.seekg(k*sizeof(int), loaded.beg);
		loaded.read((char *)&buffer, sizeof(int));
		plist.push_back(buffer);
		k++;
	}
	loaded.close();
	plist.pop_back();
	string gen=sbuf.substr(0, sbuf.find_last_of("_")) + " ";

	string filename = "./Data/Binaries/" + tagl::getid3code(gen) + ".bin";
	ifstream file(filename, ios::in | ios::binary);
	if(!file.is_open()){
		cout << "Error loading musics file";
		return;
	}
	int plsize=plist.size();
	track x;
	int j=0, i=0;
	while(i<plsize && file.good()){
		file.seekg(plist[i]*sizeof(track), file.beg);
		file.read((char *)&x, sizeof(track));
		cout << i << ". " << x.name << " - " << x. popularity << "\n   " << x.album << endl;
		j=0;
		while(x.artist[j][0] && j<4){
			cout << "      " << x.artist[j] << endl;
			j++;
		}
		cout << endl;
		i++;
	}
	file.close();
	plist.clear();

	cout << "Press 'Enter' to return to main menu";
	getchar();
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
				load();
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
	return 0;
}