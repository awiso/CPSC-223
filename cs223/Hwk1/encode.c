#include <stdio.h>
#include <ctype.h>

int main(void){
    int c; 
    int count = 0; 
    int first;
    int caps;

    while ((c = getchar()) != EOF){
        if(isalpha(c)){
            if(count == 0){
                first = c;
                caps = isupper(c);
                count++;
            }else if(count == 1){
                if(caps){
                    putchar(toupper(c));
                    count++;
                }else{
                    putchar(tolower(c));
                    count++;
                }
            }else{
                putchar(c); 
                count++; 
            }
        }else if(!isalpha(c)){
            if(count > 0){
                if(count == 1){
                    putchar(first);
                }else{
                    putchar(tolower(first));
                }
                if(count <= 3){
                    putchar('a');
                    putchar('n');
                    putchar(c);
                    count = 0;
                }else if(count >= 4){
                    putchar('o');
                    putchar(c);
                    count = 0; 
                }
            }else{
                putchar(c);
            }
        }
    }
    //printf("%c", c);
    //ungetc(c, stdin); 
    if(count > 0){
        if(count == 1){
            putchar(first);
        }else{
            putchar(tolower(first));
        }
        if(count <= 3){
            putchar('a');
            putchar('n');
        }else if(count >= 4){
            putchar('o');
        }
    }
    return 0;
}

