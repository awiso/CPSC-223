#include <stdlib.h>
#include <stdio.h>

int error = 0;

// STRUCT:
typedef struct tree {
    int numC;
    int size;
    struct tree **children;
} Tree; 

// FUNCTIONS:
// comparison function for qsort
int compareNumC(const void * a, const void * b){
    int x = (*((Tree **) b))->size;
    int y = (*((Tree **) a))->size;
    if (x > y){
        return 1;
    }else if (x < y){
        return -1;
    }else {return 0;}
}


//destroy the tree
void destroy(Tree * tree){
    for(int i = 0; i < tree->numC; i++){
        destroy(tree->children[i]);
    }
    free(tree->children);
    free(tree);
}

// parse the input
Tree * parse(void){

    Tree * root = malloc(sizeof(Tree));
    root->numC = 0;
    root->size = 1;
    root->children = NULL;


    int c; 
    while((c = getchar()) != EOF) {
        if(c == '['){
            
            root->numC++;
            root->children = realloc(root->children, sizeof(Tree *) * root->numC);
            root->children[root->numC-1] = parse();

        }else if (c == ']'){
            for(int i = 0; i < root->numC; i++){
                root->size += root->children[i]->size;
            }

            // qsort!
            // given two array items (tree pointers), compare thier numC's
            qsort(root->children, root->numC, sizeof(Tree *), &compareNumC);

            return root;
            
        }else{
            error = 1;
            return root;
        } 
    }

    error = 1;
    return root;

}

// print the tree
void print(Tree * t){
    printf("%c", '[');
    for(int i = 0; i < t->numC; i++){
        print(t->children[i]);
    }
    printf("%c", ']');
}

int main(int argc, char **argv){
    
    if(getchar() != '['){
        exit(1);
    }
     
    Tree * tree = parse();

    if(error){
        destroy(tree);
        exit(1);
    }
    print(tree); 
    destroy(tree);

} 