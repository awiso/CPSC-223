#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "num.h"

// define the num structure
struct num {
    int length; 
    int * digits;
};

Num * numCreate(const char * s){ 
    // create a Num and set its length
    Num * number; 
    number = malloc(sizeof(Num));

    int len = strlen(s); 
    char * noZeros; 
    noZeros = malloc(sizeof(char)*len);

    int start = 1;
    if(len == 1){
        if(!isdigit(s[0])){
            return 0;
        }
        noZeros[0] = s[0]; 
    }else{
        for(int i = 0; i < len; i++){
            if(!isdigit(s[i])){
                return 0; 
            }
            if(!start){
                noZeros[i] = s[i]; 

            // consider the 0000 case!
            }else if((start)&&(i == len)){
                for(int j = 0; j < len; j++){
                    noZeros[i] = '0';
                }

            }else if((start)&&(s[i] != '0')){
                    noZeros[i] = s[i];  
                    start = 0;

            }else if((start)&&(s[i] == '0')){
                noZeros[i] = 'x';
            }
        }
    }

    // filter out all x chars
    while(noZeros[0] == 'x'){
        noZeros++;
    }

    // convert noZeros to digits
    number->length = strlen(noZeros);

    number->digits = malloc(sizeof(int) * number->length); 

    for(int i = 0; i < number->length; i++){
        char c = noZeros[i]; 
        number->digits[i] = c - '0';
    }
    return number;
}

void numDestroy(Num *n){
    free(n->digits);
    free(n);
}

void numPrint(const Num *n, FILE *f){
    int count = 0;
    for(int i = 0; i < n->length; i++){
        if(n->digits[i] != 0) {
            count = i;
            break;
        }
    }
    if((count == 0) && (n->digits[0] == 0)){
        fprintf(f, "%d", 0);
    } else {
        for(int i = count; i < n->length; i++){
            fprintf(f, "%d", n->digits[i]);
        }
    }

}

int numGetDigit(const Num *n, int i){
    int highestIndex = n->length - 1; 

    if(i > highestIndex){
        return 0;
    }else if(i < 0){
        return 0; 
    }else{
        return n->digits[highestIndex - i];
    }
}

Num * numAdd(const Num *x, const Num *y){
    int xAdd, yAdd, zSum, iSum, carry = 0;

    Num * z;
    z = malloc(sizeof(Num));

    // get the length of the larger number
    int maxLen; 
    if(x->length > y->length){
        maxLen = x->length;
    }else if(x->length < y->length){
        maxLen = y->length;
    }else if(x->length == y->length){
        maxLen = x->length;
    }
    // allocate space for z's array of digits
    z->digits = malloc((sizeof(int)) * (maxLen + 1)); 

    int * temp; 
    temp = malloc((sizeof(int)) * maxLen); 

    // loop through maxLen
    // add getdigits of y and x
    for(int i = 0; i < maxLen+1; i++){
        xAdd = numGetDigit(x, i); 
        yAdd = numGetDigit(y, i);
        zSum = xAdd + yAdd + carry;

        // put this down at current index
        iSum = zSum % 10;
        temp[i] = iSum;                                  

        carry = zSum / 10;   
    }

    for(int i = maxLen; i >= 0; i--){
        z->digits[maxLen - i - 1] = temp[i];              
    }
    free(temp); 

    z->length = maxLen; 
    return z;
    //return NULL; 
}

Num * numMultiply(const Num *x, const Num *y){
    // 'sliding-door' method
    Num * z;
    z = malloc(sizeof(Num));

    if(z == 0) {
        return 0;
    }

    z->length = (x->length + y->length); 
    z->digits = calloc((x->length + y->length), sizeof(int));

    for(int i = x->length - 1; i >= 0; i--){
        for(int j = y->length - 1; j >= 0; j--){
            z->digits[i + j + 1] += x->digits[i] * y->digits[j] % 10; 
            z->digits[i + j] += x->digits[i] * y->digits[j] / 10; 

            if(z->digits[i + j + 1] >= 10){
                z->digits[i + j] += z->digits[i + j + 1] / 10;
                z->digits[i + j + 1] = z->digits[i + j + 1] % 10;
            }
        }
    } 
    return z; 
}