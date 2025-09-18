#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/* Allocate a new empty list */
list_t* list_alloc(void) {
  list_t* l = (list_t*) malloc(sizeof(list_t));
  if (!l) return NULL;
  l->head = NULL;
  return l;
}

/* Free all nodes and the list struct */
void list_free(list_t* l) {
  if (!l) return;
  node_t* curr = l->head;
  while (curr) {
    node_t* nxt = curr->next;
    free(curr);
    curr = nxt;
  }
  free(l);
}

void list_print(const list_t* l) {
  const node_t* curr = l ? l->head : NULL;
  printf("[");
  while (curr) {
    printf("%d", curr->value);
    if (curr->next) printf(", ");
    curr = curr->next;
  }
  printf("]\\n");
}

int list_length(const list_t* l) {
  int count = 0;
  const node_t* curr = l ? l->head : NULL;
  while (curr) {
    count++;
    curr = curr->next;
  }
  return count;
}

void list_add_to_front(list_t* l, elem value) {
  if (!l) return;
  node_t* n = (node_t*) malloc(sizeof(node_t));
  if (!n) return;
  n->value = value;
  n->next = l->head;
  l->head = n;
}

void list_add_to_back(list_t* l, elem value) {
  if (!l) return;
  node_t* n = (node_t*) malloc(sizeof(node_t));
  if (!n) return;
  n->value = value;
  n->next = NULL;
  if (!l->head) {
    l->head = n;
    return;
  }
  node_t* curr = l->head;
  while (curr->next) curr = curr->next;
  curr->next = n;
}

bool list_add_at_index(list_t* l, elem value, int index) {
  if (!l || index < 0) return false;
  if (index == 0) {
    list_add_to_front(l, value);
    return true;
  }
  int i = 0;
  node_t* curr = l->head;
  while (curr && i < index - 1) {
    curr = curr->next;
    i++;
  }
  if (!curr) return false;
  node_t* n = (node_t*) malloc(sizeof(node_t));
  if (!n) return false;
  n->value = value;
  n->next = curr->next;
  curr->next = n;
  return true;
}

elem list_remove_from_front(list_t* l) {
  if (!l || !l->head) {
    fprintf(stderr, "remove_front on empty list\\n");
    exit(1);
  }
  node_t* n = l->head;
  elem v = n->value;
  l->head = n->next;
  free(n);
  return v;
}

elem list_remove_from_back(list_t* l) {
  if (!l || !l->head) {
    fprintf(stderr, "remove_back on empty list\\n");
    exit(1);
  }
  if (!l->head->next) {
    elem v = l->head->value;
    free(l->head);
    l->head = NULL;
    return v;
  }
  node_t* prev = NULL;
  node_t* curr = l->head;
  while (curr->next) {
    prev = curr;
    curr = curr->next;
  }
  elem v = curr->value;
  prev->next = NULL;
  free(curr);
  return v;
}

elem list_remove_at_index(list_t* l, int index) {
  if (!l || index < 0) {
    fprintf(stderr, "remove_at_index invalid args\\n");
    exit(1);
  }
  if (index == 0) return list_remove_from_front(l);
  int i = 0;
  node_t* prev = NULL;
  node_t* curr = l->head;
  while (curr && i < index) {
    prev = curr;
    curr = curr->next;
    i++;
  }
  if (!curr) {
    fprintf(stderr, "remove_at_index out of range\\n");
    exit(1);
  }
  elem v = curr->value;
  prev->next = curr->next;
  free(curr);
  return v;
}

bool list_is_in(const list_t* l, elem value) {
  const node_t* curr = l ? l->head : NULL;
  while (curr) {
    if (curr->value == value) return true;
    curr = curr->next;
  }
  return false;
}

elem list_get_elem_at(const list_t* l, int index) {
  if (!l || index < 0) {
    fprintf(stderr, "get_elem_at invalid args\\n");
    exit(1);
  }
  int i = 0;
  const node_t* curr = l->head;
  while (curr && i < index) {
    curr = curr->next;
    i++;
  }
  if (!curr) {
    fprintf(stderr, "get_elem_at out of range\\n");
    exit(1);
  }
  return curr->value;
}

int list_get_index_of(const list_t* l, elem value) {
  int i = 0;
  const node_t* curr = l ? l->head : NULL;
  while (curr) {
    if (curr->value == value) return i;
    curr = curr->next;
    i++;
  }
  return -1;
}
