#ifndef BUBBLESORT_H
#define BUBBLESORT_H

#pragma pack(1)
typedef struct _my_struct {
    char data_string[100];
    int data_length;
    int index;
} my_struct_t;
#pragma pack()

void bubble_sort(my_struct_t structs_array[], int array_length);
void swap(my_struct_t *p_my_first_struct, my_struct_t *p_my_second_struct);

int get_struct_index(my_struct_t *p_my_struct);
void print_array(my_struct_t p_my_struct[], int array_length);


#endif //BUBBLESORT_H
