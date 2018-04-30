#include "array.h"
#include <stdio.h>

struct array{
    int (*combine)(int, int);   
    int size;
    int value;
    struct array* left;
    struct array* right;  
};

Array *arrayCreate(int (*combine)(int, int), size_t n){
    Array *root = malloc(sizeof(Array));
    if(n == 1){
        root->combine = combine;
        root->size = 1;
        root->value = 0;
        root->left = NULL;
        root->right = NULL;
    }else{
        root->combine = combine;
        root->size = n;
        root->left = arrayCreate(combine, n/2);
        root->right = arrayCreate(combine, n-n/2);
        root->value = combine(root->left->value, root->right->value);
    }
    return root;
}

void arrayDestroy(Array *a){
    if(a){
        arrayDestroy(a->left);
        arrayDestroy(a->right);
        free(a);
    }
}

size_t arraySize(const Array *a){
    return a->size;
}

// Return the i-th element of an array
// or 0 if i is out of range.
// Cost: O(log n).
int arrayGet(const Array *a, size_t i){
    // error check for out of range
    if(i >= a->size){
        return 0;
    // base case is n = 1
    }else if(a->size == 1){
        return a->value;
    }else if(i >= a->left->size){
        i -= a->left->size;
        return arrayGet(a->right, i);
    }else{
        return arrayGet(a->left, i);
    }
}

// Set the i-th element of an array to v.
// No effect if i is out of range.
// Cost: O(log n).
void arraySet(Array *a, size_t i, int v){
    if(i >= a->size){
        return;
    }
    if(a->size == 1){
        a->value = v;
    }else{
        if(i >= a->left->size){
            i -= a->left->size;
            arraySet(a->right, i, v);
        }else{
            arraySet(a->left, i, v);
        }
        a->value = a->combine(a->left->value, a->right->value);
    }
}

// Return the result of aggregating the first k elements
// of an array in order using the combine function.
// If k is zero or greater than size, returns combination of all elements.
// Cost: O(log n).
int arrayCombine(const Array *a, size_t k){
    if(k == 0 || k > a->size){
        return a->value;

    }else if(k == a->size){
        return a->value;

    }else if(k <= a->left->size){
        return arrayCombine(a->left, k);

    }else if(k > a->left->size){
        return a->combine(a->left->value, arrayCombine(a->right, k - a->left->size));
    }

    return 0;
}
