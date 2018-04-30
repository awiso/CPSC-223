#ifndef HASH_H
#define HASH_H

# include <stdio.h>

// coordinate position struct - use unsigned long int (0 - 4,294,967,295)
typedef struct coordinate {
    int x;
    int y;
    int z;
} Coordinate;

// UNIVERSE:
// hash element
typedef struct element { 
    Coordinate * coord; 
    int character;
    struct element * next; 
} Element;

// hash table
typedef struct hash {
    int size; 
    Element **array; 
} Hash;

// initialize
Hash * createHash(int size);

// hash function
int hashFunction(Coordinate *e, Hash *h); 

// delete hash
void hashDestroy(Hash *h); 

// put a value into table
void putValue(Coordinate *e, int character, Hash *h); 

// get the value at a location
int getValue(Coordinate *e, Hash *h);

// compare two elements (coordinates)
int compareCoords(Coordinate *a, Coordinate *b);

#endif
