# include <stdlib.h>
# include "hash.h"

Hash *createHash(int size){
    Hash *h = malloc(sizeof(Hash)); 
    h->size = size; 
    h->array = (Element **) malloc(sizeof(Element *) * size); 

    for(int i = 0; i < h->size; i++){
        h->array[i] = NULL; 
    }

    return h; 
}

int hashFunction(Coordinate *e, Hash *h){
    int limit = h->size; 
    int result = 0; 
    result = abs(e->x)*113 + abs(e->y)*199 + abs(e->z)*127;
    result += result % limit; // negatives!! 
    return abs(result); 
}

void hashDestroy(Hash *h){
    for(int i = 0; i < h->size; i++){

        if(h->array[i] != NULL){
            Element * temp = h->array[i];
            Element * elt; 
            while(temp){
                elt = temp->next; 
                free(temp->coord);
                free(temp);
                temp = elt;
            }
            
        }
    }
    free(h->array);
    free(h); 
}

void putValue(Coordinate *e, int character, Hash *h){
    int index = hashFunction(e, h);
    index = index % h->size; 

    if(h->array[index] == NULL){
        h->array[index] = malloc(sizeof(Element));
        h->array[index]->coord = malloc(sizeof(Coordinate));
        h->array[index]->coord->x = e->x;
        h->array[index]->coord->y = e->y;
        h->array[index]->coord->z = e->z;
        h->array[index]->character = character;
        h->array[index]->next = NULL; 

    }else{
        Element * temp1 = h->array[index];
        while(temp1){
            if(compareCoords(e, temp1->coord)){
                temp1->character = character;
                return; 
            }
            if(temp1->next != NULL){
                temp1 = temp1->next;       
            }else{
                break;
            }
        }
        Element * other = malloc(sizeof(Element));
        other->coord = malloc(sizeof(Coordinate));
        other->coord->x = e->x;
        other->coord->y = e->y;
        other->coord->z = e->z;

        other->character = character;
        other->next = NULL; 

        temp1->next = other;
    }
}

int getValue(Coordinate *e, Hash *h){
// returns the value (character) associated with a key (coordinate)
    int index = hashFunction(e, h);
    index = index % h->size; 

    Element * temp = h->array[index];

    while(temp){
        if(compareCoords(e, temp->coord) == 1){
            return temp->character;
        }
        temp = temp->next;
    }
    return ' '; 
}

int compareCoords(Coordinate *a, Coordinate *b){
    if((a->x == b->x)&&(a->y == b->y)&&(a->z == b->z)){
        return 1; 
    } else {
        return 0;
    }
}
