#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_SIZE

int convert_to_decimal(char character);

int main(){

    FILE *file_to_read, *file_to_write;
    char *bin_array[512];
    int  *dec_array[512];
    long file_size = 0;


    file_to_read = fopen("encrypted.txt", "r");

    int i;

    if(file_to_read != NULL){
        while((i = fgetc(file_to_read)) != EOF){
            int counter = 0;
           dec_array[counter] = convert_to_decimal(i);
           counter++;
        }
    }

    return 0;
}

// The idea is to convert encoded individual characters to its decimal form.
// Then convert those decimals to binary
// Then group these binary as 6bits binary.
// Then concatenate them together.
// Divide by 8 so I could get 8 bit binaries.
// And do lookup on ASCII table and convert the binaries.
// Then hopefully get readable words back

int convert_to_decimal(char character){

    char *b64_table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz+/";
    int counter = 0;

    do {
        if(strcmp((char *)character, &b64_table[counter]) == 0){
            return counter;
    }
        counter++;
    }while (counter < 64);

    return 80;
}
