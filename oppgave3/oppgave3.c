#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/doubly_linked_list.h"
#include "include/pgdbglog.h"

int main(int argc, char *argv[]){

    int selected_menu;
    char full_name_buffer[MAX_LENGTH_STRING];
    char municipality_buffer[MAX_LENGTH_STRING];
    char age_buffer[MAX_LENGTH_SMALL_INT];
    char index_buffer[MAX_LENGTH_MEDIUM_INT];
    char mode_buffer[MAX_LENGTH_SMALL_INT];

    dl_list_t my_list = {NULL, NULL};

    /*  testing leaks uncomment this and comment while loop
     *  then do valgrind --leak-check=yes ./oppgave3
     init_test_data(&my_list);
     get_index_by_name(&my_list, "Buffer Overflowin");
     get_node_by_index(&my_list, 8);
     remove_all_by_name(&my_list, "This is painful");
     get_all(&my_list);
     remove_all_by_age(&my_list, 19, 1);
     free_all(&my_list);
     */




    while(true){

        printf("========Select your action=========\n\n");
        printf("[1] Add new node\n");
        printf("[2] Find node info by index\n");
        printf("[3] Find node index by name\n");
        printf("[4] Delete all by name\n");
        printf("[5] Delete by age\n");
        printf("[6] Show all nodes\n");
        printf("[7] Add some test nodes\n");
        printf("[0] Exit\n\n");
        printf("===================================\n\n");
        selected_menu = getchar();
        getchar();

        switch (selected_menu) {

            case '1':
                system("clear");
                printf("Provide full name for this person\n");
                fgets(full_name_buffer, MAX_LENGTH_STRING, stdin);
                full_name_buffer[strlen(full_name_buffer) - 1] = '\0';
                printf("From which municipality does this person belongs to?\n");
                fgets(municipality_buffer, MAX_LENGTH_STRING, stdin);
                municipality_buffer[strlen(municipality_buffer) - 1] = '\0';
                printf("How old is this person\n");
                fgets(age_buffer, MAX_LENGTH_SMALL_INT, stdin);
                system("clear"); 
                int age = (atoi(age_buffer) == 0) ? 1 : atoi(age_buffer);
                if(my_list.p_head == NULL){
                    insert_head(&my_list, full_name_buffer, municipality_buffer, age);
                } else {
                    insert_tail(&my_list, full_name_buffer, municipality_buffer, age);
                }
                break;
            case '2':
                system("clear");
                printf("Enter the index of the node you wish to see\n");
                fgets(index_buffer, sizeof(stdin), stdin);
                system("clear");
                get_node_by_index(&my_list, atoi(index_buffer));
                break;
            case '3':
                system("clear");
                printf("Provide the name to find the index\n");
                fgets(full_name_buffer, MAX_LENGTH_STRING, stdin);
                system("clear");
                full_name_buffer[strlen(full_name_buffer) - 1] = '\0';
                get_index_by_name(&my_list, full_name_buffer);
                break;
            case '4':
                system("clear");
                printf("Provide the name you wish to all remove\n");
                fgets(full_name_buffer, MAX_LENGTH_STRING, stdin);
                system("clear");
                full_name_buffer[strlen(full_name_buffer) - 1] = '\0';
                remove_all_by_name(&my_list, full_name_buffer);
                break;
            case '5':
                system("clear");
                printf("Enter an age\n");
                fgets(age_buffer, MAX_LENGTH_SMALL_INT, stdin);
                system("clear");
                printf("Choose the operation you wish to do with that age\n\n");
                printf("[1] Remove all equal to %s\n", age_buffer);
                printf("[2] Remove all lesser than %s\n", age_buffer);
                printf("[3] Remove all greater than %s\n", age_buffer);
                fgets(mode_buffer, MAX_LENGTH_SMALL_INT, stdin);
                system("clear");
                remove_all_by_age(&my_list, atoi(age_buffer), atoi(mode_buffer));
                break;
            case '6':
                system("clear");
                get_all(&my_list);
                break;
            case '7':
                system("clear");
                init_test_data(&my_list);
                break;
            case '0':
                system("clear");
                printf("Exiting...\n");
                free_all(&my_list);
                return 0;
            default:
                printf("Command not found %i\n\n", selected_menu);
                break;
        }
    }
    return 0;
}


void init_test_data(dl_list_t *p_dl_list){
    printf("==============Completed============\n\n");
    insert_head(p_dl_list, "Lmao", "From behind xd", 23);
    insert_tail(p_dl_list, "Test man", "Test asdasd", 32);
    insert_tail(p_dl_list, "Crashing program", "stack is fked", 32);
    insert_tail(p_dl_list, "Buffer Overflowin", "how to free", 32);
    insert_tail(p_dl_list, "This is painful", "pain", 32);
    insert_tail(p_dl_list, "Lmao", "From behind xd", 19);
    insert_tail(p_dl_list, "Lmao", "From behind xd", 21);
    insert_tail(p_dl_list, "In between", "checking", 53);
    insert_tail(p_dl_list, "Lmao", "From behind xd", 23);
    printf("Inserted 9 test data\n\n");
    printf("===================================\n\n");
}

static list_node_t *create_node(char *p_full_name, char *p_municipality, unsigned int age){
    list_node_t *p_current = malloc(sizeof(list_node_t));

    if(p_current == NULL){
        printf("Could not allocate memory for this node");
        return 0;
    }


    memset(p_current, 0, sizeof(list_node_t));
    p_current->p_full_name = malloc(sizeof(char) * (strlen(p_full_name)+1));
    strcpy(p_current->p_full_name, p_full_name);
    p_current->p_municipality = malloc(sizeof(char) * (strlen(p_municipality)+1));
    strcpy(p_current->p_municipality, p_municipality);
    p_current->age = age;

    return p_current;
}

bool insert_head(dl_list_t *p_dl_list, char *p_full_name, char *p_municipality, unsigned int age){

    list_node_t *p_current = create_node(p_full_name, p_municipality, age);
    if(p_current != NULL){
        if(p_dl_list->p_head == NULL){
            p_dl_list->p_head = p_current;
            p_dl_list->p_tail = p_current;
            printf("Inserted head node [%s]\n", p_current->p_full_name);
            return true;
        } else {
            insert_before(p_dl_list, p_dl_list->p_head, p_current);
            return true;
        }
    }
    return false;
}

void insert_before(dl_list_t *p_dl_list, list_node_t *p_before_node, list_node_t *p_new_node){
    p_new_node->p_next = p_before_node;
    if(p_before_node->p_prev == NULL){
        p_dl_list->p_head = p_new_node;
    } else {
        p_new_node->p_prev = p_before_node->p_prev;
        p_before_node->p_prev->p_next = p_new_node;
    }
    p_before_node->p_prev = p_new_node;
    printf("Insert node as new head node [%s]\n", p_new_node->p_full_name);
}

bool insert_tail(dl_list_t *p_dl_list, char *p_full_name, char *p_municipality, unsigned int age){

    list_node_t *p_current = create_node(p_full_name, p_municipality, age);
    if(p_current != NULL){
        if(p_dl_list->p_head == NULL){
            p_dl_list->p_head = p_current;
            p_dl_list->p_tail = p_current;
            return true;
        } else {
            insert_after(p_dl_list, p_dl_list->p_tail, p_current);
            return true;
        }
    }
    return false;
}

void insert_after(
        dl_list_t *p_dl_list,
        list_node_t *p_after_node,
        list_node_t *p_new_node
        ){

    p_new_node->p_prev = p_after_node;

    if(p_after_node->p_next == NULL){
        p_new_node->p_next = NULL;
        p_dl_list->p_tail = p_new_node;
    } else {
        p_new_node->p_next = p_after_node->p_next;
        p_after_node->p_next->p_prev = p_new_node;
    }

    p_after_node->p_next = p_new_node;
    printf("Insert node as new tail node [%s]\n", p_new_node->p_full_name);
}

bool get_node_by_index(dl_list_t *p_dl_list, unsigned int index){

    int counter = 1;
    list_node_t *p_current = p_dl_list->p_head;

    if(p_dl_list->p_head == NULL){

        printf("==============Error===============\n\n");
        printf("Cannot traverse through empty list\n\n");
        printf("==================================\n\n");
        return false;
    }

    if(index <= 0){


        printf("==============Error===============\n\n");
        printf("Invalid index: %i please provide non-negative/zero values\n\n", index);
        printf("==================================\n\n");
        return false;
    }

    bool found = false;

    while(p_current != NULL){

        if(counter == index){
            printf("==============Found===============\n\n");
            printf("Full name: %s\nAge: %i\nMunicipality: %s\n\n",
                    p_current->p_full_name,
                    p_current->age,
                    p_current->p_municipality);
            printf("==================================\n\n");
            found = true;
            break;
        }
        p_current = p_current->p_next;
        counter++;
    }

    if(!found){
        printf("==============Failed==============\n\n");
        printf("Could not find anything at index: %i\n\n", index);
        printf("===============Done===============\n\n");
        return false;
    }

    return true;
}


bool get_index_by_name(dl_list_t *p_dl_list, char *p_search_string){

    if(p_dl_list->p_head == NULL){
        printf("================Error==============\n\n");
        printf("Cannot get index from empty list\n\n");
        printf("===================================\n\n");
        return false;
    }

    int index = 1;
    list_node_t *p_current = p_dl_list->p_head;
    bool found = false;

    printf("==============Completed============\n\n");
    while(p_current != NULL){

        bool is_matching = (strcmp(p_current->p_full_name, p_search_string) == 0);

        if(is_matching){
            printf("Found '%s' at index: %i \n\n", p_search_string, index);
            found = true;
            printf("===================================\n\n");
            return true;
        }
        index++;
        p_current = p_current->p_next;
    }

    if(!found){
        printf("Could not find index for %s\n\n", p_search_string);
    }
    printf("===================================\n\n");
    return false;
}

void get_all(dl_list_t *p_dl_list){
    if(p_dl_list->p_head == NULL){
        printf("================Error==============\n\n");
        printf("Could not traverse through empty list\n\n");
        printf("===================================\n\n");
        return;
    }

    list_node_t *p_current = p_dl_list->p_head;



    printf("=============Success===============\n\n");

    while(p_current != NULL){
        if(p_current->p_prev == NULL){
            if(p_current->p_next == NULL){
                printf("(HEAD)[%s, %i](TAIL)", p_current->p_full_name, p_current->age);
            }else{
                printf("(HEAD)[%s, %i]-", p_current->p_full_name, p_current->age);
            }
        }else if(p_current->p_next == NULL){
            printf("[%s, %i](TAIL)", p_current->p_full_name, p_current->age);
        } else {
            printf("[%s, %i]-", p_current->p_full_name, p_current->age);
        }
        p_current = p_current->p_next;
    }

    printf("\n\n===================================\n\n");

}

void remove_all_by_name(dl_list_t *p_dl_list, char *search_string){


    if(p_dl_list->p_head == NULL){
        printf("==============Error================\n\n");
        printf("Cannot delete from empty list\n\n");
        printf("===================================\n\n");
        return;
    }

    list_node_t *p_current = p_dl_list->p_head;
    int counter = 0;

    bool freed = false;

    printf("============Completed==============\n\n");


    while(p_current != NULL){

        list_node_t *p_next_temp = p_current->p_next;

        if(strcmp(p_current->p_full_name, search_string) == 0){

            if(p_current->p_prev  == NULL && p_current->p_next == NULL){
                printf("Removing last node in the list...\n");
                free_last(p_dl_list, p_current);
                freed = true;
                counter++;
            } else if(p_current->p_prev == NULL && p_current->p_next != NULL){
                printf("Removing head node...\n");
                p_dl_list->p_head = p_current->p_next;
                p_dl_list->p_head->p_prev = NULL;
                free_node(p_current);
                freed = true;
                counter++;
            } else if(p_current->p_next == NULL && p_current->p_prev != NULL){
                printf("Removing tail node...\n");
                p_dl_list->p_tail = p_current->p_prev;
                p_dl_list->p_tail->p_next = NULL;
                free_node(p_current);
                freed = true;
                counter++;
            } else {
                printf("Removing non head/tail node...\n");
                p_current->p_prev->p_next = p_current->p_next;
                p_current->p_next->p_prev = p_current->p_prev;
                free_node(p_current);
                freed = true;
                counter++;
            }
        }

        if(!freed){
            p_current = p_current->p_next;
        } else {
            p_current = p_next_temp;
            freed = false;
        }
    }
    printf("Removed total of %i nodes with name: %s\n\n", counter, search_string);
    printf("==================================\n\n");
}

void remove_all_by_age(dl_list_t *p_dl_list, unsigned int age, unsigned int mode){

    if(mode <= 0 || mode >= 4){
        printf("Unknown mode-> %i\n", mode);
        return;
    }

    list_node_t *p_current = p_dl_list->p_head;

    if(p_current == NULL){
        printf("==============Error================\n\n");
        printf("Cannot delete from empty list\n\n");
        printf("===================================\n\n");
        return;
    }

    int counter = 0;

    printf("============Completed==============\n\n");

    while(p_current != NULL){


        // Somewhat ugly but it works!
        bool age_equal_to_input = (p_current->age == age) && mode == 1;
        bool age_lesser_than_input = (p_current->age < age) && mode == 2;
        bool age_greater_than_input = (p_current->age > age) && mode == 3;
        bool freed = false;


        bool selected_any_mode = age_equal_to_input || age_lesser_than_input || age_greater_than_input;

        list_node_t *p_next_temp = p_current->p_next;

        if(selected_any_mode){

            if(p_current->p_prev  == NULL && p_current->p_next == NULL){
                printf("Removing last node in the list...\n");
                free_last(p_dl_list, p_current);
                freed = true;
                counter++;
            } else if(p_current->p_prev == NULL && p_current->p_next != NULL){
                printf("Removing head node...\n");
                p_dl_list->p_head = p_current->p_next;
                p_dl_list->p_head->p_prev = NULL;
                free_node(p_current);
                freed = true;
                counter++;
            } else if(p_current->p_next == NULL && p_current->p_prev != NULL){
                printf("Removing tail node...\n");
                p_dl_list->p_tail = p_current->p_prev;
                p_dl_list->p_tail->p_next = NULL;
                free_node(p_current);
                freed = true;
                counter++;
            } else {
                printf("Removing non head/tail node...\n");
                p_current->p_prev->p_next = p_current->p_next;
                p_current->p_next->p_prev = p_current->p_prev;
                free_node(p_current);
                freed = true;
                counter++;
            }
        }

        if(!freed){
            p_current = p_current->p_next;
        } else {
            p_current = p_next_temp;
        }
    }

    switch (mode) {
        case 1:
            printf("Removed total of %i nodes having age equal to %i\n\n", counter, age);
            break;
        case 2:
            printf("Removed total of %i nodes having age lesser than %i\n\n", counter, age);
            break;
        case 3:
            printf("Removed total of %i nodes having age greater than %i\n\n", counter, age);
            break;
        default:
            //Should not happend, if it does log the error.
            printf("Unknown error has occured with mode: %i\n\n", mode);
            log_error("Unknown error has occured with following input: age=%i mode=%i", age, mode);
            break;
    }

    printf("==================================\n\n");
}

void free_node(list_node_t *p_node_to_free){
    free(p_node_to_free->p_full_name);
    free(p_node_to_free->p_municipality);
    free(p_node_to_free);
    p_node_to_free = NULL;
}

void free_last(dl_list_t *p_dl_list, list_node_t *p_last_node){
    free(p_last_node->p_full_name);
    free(p_last_node->p_municipality);
    free(p_last_node);
    p_dl_list->p_head = NULL;
    p_dl_list->p_tail = NULL;
}

void free_all(dl_list_t *p_dl_list_t){

    if(p_dl_list_t->p_head == NULL){
        return;
    }

    list_node_t *p_current = p_dl_list_t->p_head;

    while(p_current != NULL){
        list_node_t *p_next = p_current->p_next;
        free_node(p_current);
        p_current = p_next;
    }
}


