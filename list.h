#ifndef LIST_H
#define LIST_H

#include <stdbool.h>

typedef int elem;

typedef struct node {
  elem value;
  struct node* next;
} node_t;

typedef struct list {
  node_t* head;
} list_t;

/* Allocation and deallocation */
list_t* list_alloc(void);
void list_free(list_t* l);

/* Utility / inspection */
void list_print(const list_t* l);
int list_length(const list_t* l);
bool list_is_in(const list_t* l, elem value);
elem list_get_elem_at(const list_t* l, int index);   /* 0-based; undefined if out of range */
int list_get_index_of(const list_t* l, elem value);  /* -1 if not found */

/* Insertions */
void list_add_to_front(list_t* l, elem value);
void list_add_to_back(list_t* l, elem value);
bool list_add_at_index(list_t* l, elem value, int index); /* 0..length allowed */

/* Removals (return removed value; undefined if list empty / out of range) */
elem list_remove_from_front(list_t* l);
elem list_remove_from_back(list_t* l);
elem list_remove_at_index(list_t* l, int index);

#endif /* LIST_H */
