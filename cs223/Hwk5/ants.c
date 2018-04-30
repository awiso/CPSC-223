# include <stdio.h>
# include <stdlib.h>
# include "hash.h"

// single ant structure
typedef struct ant {
    Coordinate * pos; 
} Ant;

// ANTS
Ant * createAnts(){
    //Ant * colony[256];
    Ant * colony = malloc(sizeof(Ant) * 256);
    for(int i = 0; i < 256; i++){
        colony[i].pos = malloc(sizeof(Coordinate)); 
        colony[i].pos->x = 0;
        colony[i].pos->y = 0;
        colony[i].pos->z = 0;
    }
    return colony;
}

// MAIN 
int main(void){
    
    // make a hash table, and a colony of ants
    Hash *h = createHash(99997);
    Ant * colony = createAnts();
    
    int currentAnt = 0;
    //printf("the first ant is: %c\n", currentAnt); 
    int c; 
    int getNewChar = 0; 

    // while there are characters
    while((c = getchar()) != EOF){


        // commands
        if (getNewChar == 0){
            currentAnt = c;

            getNewChar = 1;
            continue; 
        }
        switch(c){
            case 'h': //move West                     
                colony[currentAnt].pos->x = colony[currentAnt].pos->x-1; 
                break;      
            case 'j': //move South                     
                colony[currentAnt].pos->y = colony[currentAnt].pos->y-1;
                break;
            case 'k': //move North                     
                colony[currentAnt].pos->y = colony[currentAnt].pos->y+1;
                break;
            case 'l': //move East                     
                colony[currentAnt].pos->x = colony[currentAnt].pos->x+1;
                break;
            case '<': //move Up                     
                colony[currentAnt].pos->z = colony[currentAnt].pos->z+1;
                break;
            case '>': //move Down                     
                colony[currentAnt].pos->z = colony[currentAnt].pos->z-1; 
                break;
            case '*': //move x 2 jump                     
                colony[currentAnt].pos->x = colony[currentAnt].pos->x*2;
                colony[currentAnt].pos->y = colony[currentAnt].pos->y*2;
                colony[currentAnt].pos->z = colony[currentAnt].pos->z*2;
                break;

            case '.': //write ant's character into hash 
                putValue(colony[currentAnt].pos, currentAnt, h);
                break;

            case '?': //read and print character
                putchar(getValue(colony[currentAnt].pos, h));
                break;

            case '\n':
                getNewChar = 0;
                
                break;
        }
    }

    for(int i = 0; i < 256; i++){
        free(colony[i].pos);
    }
    free(colony);
    hashDestroy(h);

    return 0; 
}
