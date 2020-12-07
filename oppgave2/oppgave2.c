#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/bubblesort.h"

// This program is supposed to bubblesort struct alphabetically by its fields name.
// I might have misunderstood this part.
// "Structen skal inneholde tekstrengen... og en 'peker' til arrayet structen er en del av".
// I have assigned indices to the struct in the loop and not used the pointer?
// get_struct_index works anyway since were required to only a struct as paramete..
// Since the sorting algorithm supposed to only sort struct's content alphabetically.
// I would then assume it does not really matter much.

int main(int argc, char *argv[]){

    my_struct_t *p_struct_array;
    int array_length = argc - 1;


    if(array_length < 2){
        printf("You have to provide more than 1 arguement\n");
        return 1;
    }

    p_struct_array = malloc(array_length * sizeof(my_struct_t));
    if(p_struct_array == NULL){
        printf("Could not allocate memory for structures\n");
        free(p_struct_array);
        return 1;
    }

    for(int i = 1; i < array_length + 1; i++){
        strcpy(p_struct_array[i - 1].data_string, argv[i]);
        p_struct_array[i - 1].data_length = strlen(argv[i]);
        p_struct_array[i - 1].index = i - 1;
    }

    printf("\t======== Before sorting =========\n");

    print_array(p_struct_array, array_length);
    bubble_sort(p_struct_array, array_length);

    printf("\t======== After sorting ==========\n");

    print_array(p_struct_array, array_length);
    free(p_struct_array);
    p_struct_array = NULL;

    return 0;

}

void bubble_sort(my_struct_t structs_array[], int array_size){

    bool swapped = true;

    while(swapped){

        swapped = false;

        for(int i = 0; i < array_size - 1; i++){
            int j = i + 1;

            if(strcmp(structs_array[i].data_string, structs_array[j].data_string) > 0){
                swap(&structs_array[i], &structs_array[j]);
                swapped = true;
            }

        }

    }
}

void swap(my_struct_t *p_first_struct, my_struct_t *p_second_struct){
    my_struct_t p_temp_struct = *p_first_struct;
    *p_first_struct = *p_second_struct;
    *p_second_struct = p_temp_struct;

}

int get_struct_index(my_struct_t *p_my_struct){
    return p_my_struct->index;
}

void print_array(my_struct_t *p_struct, int array_length){
    for(int i = 0; i < array_length; i++){
        printf("struct@index::[%i] data: %-10s data-length:[%i] \n",
                p_struct[i].index,
                p_struct[i].data_string,
                p_struct[i].data_length);
    }
}
