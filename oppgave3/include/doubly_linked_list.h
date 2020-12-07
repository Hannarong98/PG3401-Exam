#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#define MAX_LENGTH_STRING 64
#define MAX_LENGTH_SMALL_INT 6
#define MAX_LENGTH_MEDIUM_INT 16

#pragma pack(1)
typedef struct _list_node {
    struct _list_node *p_next;
    struct _list_node *p_prev;
    char *p_full_name;
    char *p_municipality;
    unsigned int age;

} list_node_t;
#pragma pack()

#pragma pack(1)
typedef struct _dl_list {
    list_node_t *p_head;
    list_node_t *p_tail;
} dl_list_t;
#pragma pack()

bool insert_head(dl_list_t *p_dl_list, char *p_full_name, char *municipality, unsigned int age);

bool insert_tail(dl_list_t *p_dl_list, char *p_full_name, char *municipality, unsigned int age);

void insert_before(dl_list_t *p_dl_list, list_node_t *p_before_node, list_node_t *p_new_node);

void insert_after(dl_list_t *p_dl_list, list_node_t *p_after_node, list_node_t *p_new_node);

void init_test_data(dl_list_t *p_dl_list);

bool get_node_by_index(dl_list_t *p_dl_list, unsigned int index);

bool get_index_by_name(dl_list_t *p_dl_list, char *p_search_string);

void get_all(dl_list_t *p_dl_list);

void remove_all_by_name(dl_list_t *p_dl_list, char *p_search_string);

void remove_all_by_age(dl_list_t *p_dl_list, unsigned int age, unsigned int mode);

void free_node(list_node_t *p_node_to_free);

void free_last(dl_list_t *p_dl_list, list_node_t *p_last_node);

void free_all(dl_list_t *p_dl_list);

#endif //DOUBLY_LINKED_LIST_H
