#include <stdio.h> 
#include <stdlib.h>

int
main(int argc, char **argv)
{  
    if(argc != 4){
        return 1;
    }
    int c; 
    int n = atoi(argv[1]);

    if(n < 0){
        return 1;
    }

    long a = atoi(argv[2]);
    long b = atoi(argv[3]);

    int arr[n];
    int counter = 0; 
    while((c = getchar()) != EOF){
        arr[counter] = c; 
        counter++; 
        if(counter == n){
            for(int i = 0; i < n; i++){
                putchar(arr[((((a*i)+b) % n + n) %n)]);
            }
            counter = 0;
        }        
    }
    if(counter != 0){
        for(int i = counter; i < n; i++){
            arr[i] = '\0';
        }

        for(int j = 0; j < n; j++){
            putchar(arr[((((a*j)+b) % n + n) %n)]);
        }
    }
    return 0;
}
