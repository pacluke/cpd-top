//
//  code.c
//  trabalho cpd
//
//  Created by Lucas Flores on 6/9/16.
//  Copyright © 2016 pacluke.com. All rights reserved.
//

#include "code.h"
#include <stdio.h>
#include <string.h>

typedef struct type_track {
    
    char name[100];
    char album[100];
    char artist[100];
    char popularity[5];
    
} track;

struct playlist {
    
    track song;
    
    struct playlist *next;
    struct playlist *prev;
    
};


void makePlaylist(){
    
    const char s[2] = {','};
    char *token = NULL;
    char line[100];
    char *result;
    track songs[100];
    
    FILE *arq;
    if((arq = fopen("Data/PopNacional.txt", "r")) == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
    }
    
    int i = 0;
    while (!feof(arq) && i<100){
        
        result = fgets(line, 100, arq);
        
        if (result)
            token = strtok(result, s);
        
        int j = 0;
        while( token != NULL )
        {
            
            switch(j)
            {
                case 0:
                    strcpy(songs[i].album, token);
                    printf( "Album: %s\n", token );
                    break;
                case 1:
                    strcpy(songs[i].artist, token);
                    printf( "Artist: %s\n", token );
                    break;
                case 2:
                    strcpy(songs[i].name, token);
                    printf( "Track: %s\n", token );
                    break;
                case 3:
                    strcpy(songs[i].popularity, token);
                    printf( "Popularity: %s\n", token );
                    break;
                default:
                    break;
            }
            
            
            token = strtok(NULL, s);
            j++;
        }
        i++;
    }
    fclose(arq);
    
}