# include <stdlib.h>
# include <stdio.h> 
# include "deck.h"

// structs: 

// cards are placed in containers that can be linked
typedef struct container {
    struct container *next; 
    Card card;
} Container;

// Deck is linked list of containers holding cards
struct deck {
    Container *head; 
    Container *tail;
}; 

// functions:

Deck *deckCreate(void){
    // create empty Deck
    Deck * d;
    d = malloc(sizeof(Deck));

    // set head and tail to 0
    d->head = 0; 
    d->tail = 0; 

    // fill Deck
    for(int i = 0; i < 4; i++){
        char suit = SUITS[i]; 
        for(int j = 0; j < 13; j++){
            char rank = RANKS[j];
            Card c; 
            c.rank = rank; 
            c.suit = suit; 
            deckPutCard(d, c); 
        }
    }
    return d; 
}

int deckNotEmpty(const Deck *d){
    if(d->head == 0){
        return 0; 
    } else {
        return 1; 
    }
}

void deckPutCard(Deck *d, Card c){ 
    Container * cont = malloc(sizeof(Container));

    cont->card = c; 
    cont->next = 0;

    if(deckNotEmpty(d)){
        d->tail->next = cont; 
    } else {
        d->head = cont; 
    }
    d->tail = cont; 
}

static void cardPrint(Card c, FILE *f){
    fprintf(f, "%c%c", c.rank, c.suit); 
}

void deckPrint(const Deck *d, FILE *f){
    Container *cont;
    cont = d->head;  
    while(cont){
        cardPrint(cont->card, f);
        if(cont->next){
            fprintf(f, "%c", ' '); 
        }
        cont = cont->next; 
    }
}

Card deckGetCard(Deck *d){
    // make the return card, give it correct values
    Card ret;
    ret.rank = d->head->card.rank;
    ret.suit = d->head->card.suit; 

    // move the head pointer to the next node, free old head
    Container * temp; 
    temp = d->head;
    d->head = d->head->next; 
    free(temp); 

    return ret;
}

void deckDestroy(Deck *d){

    while(deckNotEmpty(d)){
        deckGetCard(d);
    }
    free(d);
} 

void deckSplit(Deck *d, int n, Deck **d1, Deck **d2){
    *d1 = malloc(sizeof(Deck));
    *d2 = malloc(sizeof(Deck));
    
    if(n == 0){
        (*d1)->head = 0;
        (*d1)->tail = 0;

        (*d2)->head = d->head;
        (*d2)->tail = d->tail;

    } else {
        (*d1)->head = d->head;
        Container * temp = d->head;
        for(int i = 0; i < n-1; i++){
            if(temp->next){
                temp = temp->next;
            }else{
                continue;
            }
        }
        (*d1)->tail = temp;

        (*d2)->head = (*d1)->tail->next;
        (*d2)->tail = d->tail;

        // remove the link between d1 tail and d2 head
        (*d1)->tail->next = 0;
    }
    free(d);
}

Deck *deckShuffle(Deck *d1, Deck *d2){
    Deck * d3 = malloc(sizeof(Deck));
    d3->head = 0;
    d3->tail = 0;

    if(!deckNotEmpty(d1)){
        d3->head = d2->head;
        d3->tail = d2->tail;
    }else if(!deckNotEmpty(d2)){
        d3->head = d1->head;
        d3->tail = d1->tail;
    }else{
        int boo = 1; 
        while((deckNotEmpty(d1))&&(deckNotEmpty(d2))){
            if(boo == 1){
                deckPutCard(d3, deckGetCard(d1));
            }else if(boo == -1){
                deckPutCard(d3, deckGetCard(d2));
            }
            boo *= -1;
        }

        if(deckNotEmpty(d1)){
            d3->tail->next = d1->head;
            d3->tail = d1->tail;
        }else if(deckNotEmpty(d2)){
            d3->tail->next = d2->head;
            d3->tail = d2->tail;
        }
    }

    free(d1);
    free(d2);

    return d3;
}