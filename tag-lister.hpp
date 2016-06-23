#ifndef TAG_LISTER_HPP
#define TAG_LISTER_HPP

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

//tagl::listall(); Lists all available genres and their respective ID3 tag codes.

using namespace std;

namespace tagl{
	int * getgenres(int *ngens){
		int *genrearray, i;
		char buffer[50];
		FILE *fp=fopen("config.ini", "r");
		if(!fp){
			cout << "File missing: config.ini" << endl;
			return 0;
		}
		fscanf(fp, "%49s ", buffer);
		if(strcmp(buffer, "genre_n:")){
			cout << "Error in config.ini's syntax" << endl;
			return 0;
		}

		fscanf(fp, "%d", ngens);

		genrearray= (int *) malloc((*ngens)*sizeof(int));
		if(!genrearray){
			cout << "Error in memory allocation." << endl;
			return 0;
		}

		fscanf(fp, "%49s ", buffer);
		if(strcmp(buffer, "genres:")){
			cout << "Error in config.ini's syntax" << endl;
			return 0;
		}

		for(i=0;i<*ngens-1;i++){
			fscanf(fp, "%d, ", (genrearray+i));
		}
		fscanf(fp, "%d", (genrearray+i));
		fclose(fp);

		return genrearray;
	}

	string getid3(int code){
		int buffer=-1;
		char genre[100];
		FILE *fp=fopen("./Data/ID3-genres.txt", "r");
		if(!fp){
			return "File missing: /Data/ID3-genres.txt";
		}
		while(buffer<code){
			fscanf(fp, "%d = %99[^\n]s", &buffer, genre);
		}
		return genre;
	}

	string getid3code(string gen){
		char buffer[101]="", code[5]="";
		FILE *fp=fopen("./Data/ID3-genres.txt", "r");
		if(!fp){
			return "File missing: /Data/ID3-genres.txt";
		}
		while(gen.compare(buffer) && strcmp(code, "255")){
			fscanf(fp, "%s = %99[^\n]s ", code, buffer);
		}
		return code;
	}

	void listall(){
		int *genrearray=0, ngens;
		genrearray = getgenres(&ngens);
		cout << ngens << " genres found:\n\n";

		for(int i=0; i<ngens; i++){
			cout << genrearray[i] << "-" << getid3(genrearray[i]) << endl;
		}
		free(genrearray);
	}
}

#endif //TAG_LISTER_HPP