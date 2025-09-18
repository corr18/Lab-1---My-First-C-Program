#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

// Allocate a new list
list_t *list_alloc() { 
  list_t* mylist = (list_t *) malloc(sizeof(list_t)); 
  mylist->head = NULL;
  return mylist;
}

// Free all nodes and the list itself
void list_free(list_t *l) {
  node_t *curr = l->head;
  while (curr != NULL) {
    node_t *tmp = curr;
    curr = curr->next;
    free(tmp);
  }
  free(l);
}

// Print list to stdout
void list_print(list_t *l) {
  node_t *curr = l->head;
  while (curr != NULL) {
    printf("%d -> ", curr->value);
    curr = curr->next;
  }
  printf("NULL\n");
}

// Helper: create a new node
node_t* getNode(int val) {
  node_t* n = (node_t *) malloc(sizeof(node_t));
  n->value = val;
  n->next = NULL;
  return n;
}

// Convert list to string
char *listToString(list_t *l) {
  char* buf = (char *) malloc(sizeof(char) * 1024);
  buf[0] = '\0';  // initialize buffer

  node_t *curr = l->head;
  char tbuf[64];

  while (curr != NULL) {
    sprintf(tbuf, "%d->", curr->value);
    strcat(buf, tbuf);
    curr = curr->next;
  }
  strcat(buf, "NULL");
  return buf;
}

// Count length
int list_length(list_t *l) {
  int count = 0;
  node_t *curr = l->head;
  while (curr != NULL) {
    count++;
    curr = curr->next;
  }
  return count;
}

// Add to back
void list_add_to_back(list_t *l, elem value) {
  node_t *n = getNode(value);
  if (l->head == NULL) {
    l->head = n;
    return;
  }
  node_t *curr = l->head;
  while (curr->next != NULL) {
    curr = curr->next;
  }
  curr->next = n;
}

// Add to front
void list_add_to_front(list_t *l, elem value) {
  node_t *n = getNode(value);
  n->next = l->head;
  l->head = n;
}

// Add at index
void list_add_at_index(list_t *l, elem value, int index) {
  if (index == 0) {
    list_add_to_front(l, value);
    return;
  }
  node_t *curr = l->head;
  for (int i = 0; curr != NULL && i < index - 1; i++) {
    curr = curr->next;
  }
  if (curr == NULL) return; // index too large
  node_t *n = getNode(value);
  n->next = curr->next;
  curr->next = n;
}

// Remove from back
elem list_remove_from_back(list_t *l) {
  if (l->head == NULL) return -1;
  if (l->head->next == NULL) {
    int val = l->head->value;
    free(l->head);
    l->head = NULL;
    return val;
  }
  node_t *curr = l->head;
  while (curr->next->next != NULL) {
    curr = curr->next;
  }
  int val = curr->next->value;
  free(curr->next);
  curr->next = NULL;
  return val;
}

// Remove from front
elem list_remove_from_front(list_t *l) {
  if (l->head == NULL) return -1;
  node_t *tmp = l->head;
  int val = tmp->value;
  l->head = tmp->next;
  free(tmp);
  return val;
}

// Remove at index
elem list_remove_at_index(list_t *l, int index) {
  if (l->head == NULL) return -1;
  if (index == 0) return list_remove_from_front(l);

  node_t *curr = l->head;
  for (int i = 0; curr->next != NULL && i < index - 1; i++) {
    curr = curr->next;
  }
  if (curr->next == NULL) return -1; // out of bounds
  node_t *tmp = curr->next;
  int val = tmp->value;
  curr->next = tmp->next;
  free(tmp);
  return val;
}

// Check membership
bool list_is_in(list_t *l, elem value) {
  node_t *curr = l->head;
  while (curr != NULL) {
    if (curr->value == value) return true;
    curr = curr->next;
  }
  return false;
}

// Get element at index
elem list_get_elem_at(list_t *l, int index) {
  node_t *curr = l->head;
  int i = 0;
  while (curr != NULL) {
    if (i == index) return curr->value;
    curr = curr->next;
    i++;
  }
  return -1; // not found
}

// Get index of element
int list_get_index_of(list_t *l, elem value) {
  node_t *curr = l->head;
  int i = 0;
  while (curr != NULL) {
    if (curr->value == value) return i;
    curr = curr->next;
    i++;
  }
  return -1; // not found
}

