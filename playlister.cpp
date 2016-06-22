#include <iostream>
#include <algorithm>
#include "tag-lister.hpp"
#include "formattedJSON-parser.hpp"

void cls(){ ///Cleans the console screen in a "Cabreiro" way.
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

void generate(){
	int op;
	tagl::listall();
	cout << "Type desired genre: ";
	cin >> op;
	//if(!parsed(op)){
	fjson::parse(op);
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