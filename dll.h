#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef DLL_H_
#define DLL_H_

typedef struct NODE {
  char *item;
  struct NODE *next;
  struct NODE *prev;

} NODE;

typedef struct DLL {
  NODE *head;
  NODE *tail;
} DLL;

DLL *dll_new();
int dll_insert(DLL *dll, char *item);
int dll_delete(DLL *dll, char *item);
NODE *dll_find(DLL *dll, char *needle);
void dll_print(DLL *dll);
void dll_free(DLL *dll);

#endif // DLL_H_

#ifdef DLL_IMPLEMENTAION

DLL *dll_new() {

  DLL *dll = (DLL *)malloc(sizeof(DLL));
  if (dll == NULL) {
    fprintf(stderr, "ERROR: Allocating Linked List faild: %s\n",
            strerror(errno));
    return NULL;
  }
  NODE *head = (NODE *)calloc(1, sizeof(NODE));
  NODE *tail = (NODE *)calloc(1, sizeof(NODE));
  if (head == NULL || tail == NULL) {
    fprintf(stderr, "The allocation of the init NODEs faild with : %s\n",
            strerror(errno));
    return NULL;
  }

  dll->head = head;
  dll->tail = tail;
  dll->head->next = dll->tail;
  dll->head->prev = dll->tail;
  dll->tail->prev = dll->head;
  dll->tail->next = dll->head;

  return dll;
}

int dll_insert(DLL *dll, char *item) {
  NODE *new_node = (NODE *)calloc(1, sizeof(NODE));
  if (new_node == NULL) {
    fprintf(stderr, "The allocation of a new node faild with : %s\n",
            strerror(errno));
    return 1;
  }

  new_node->next = dll->tail;
  new_node->prev = dll->tail->prev;
  dll->tail->prev->next = new_node;
  dll->tail->prev = new_node;
  new_node->item = item;

  return 0;
}

int dll_delete(DLL *dll, char *item) {
  NODE *item_node = dll_find(dll, item);
  if (item_node == NULL) {
    return 0;
  }
  item_node->prev->next = item_node->next;
  item_node->next->prev = item_node->prev;
  free(item_node);

  return 1;
}

NODE *dll_find(DLL *dll, char *needle) {
  NODE *temp;
  temp = dll->head->next;
  while (temp != dll->tail) {
    if (strcmp(needle, temp->item) == 0)
      return temp;
    temp = temp->next;
  }

  return NULL;
}

void dll_print(DLL *dll) {
  NODE *temp;
  temp = dll->head->next;
  int i = 1;
  while (temp != dll->tail) {
    printf("Item%d: %s \n", i, temp->item);
    ++i;
    temp = temp->next;
  }
}

void dll_free(DLL *dll) {
  free(dll->head);
  free(dll->tail);
  free(dll);
}

#endif // DLL_IMPLEMENTAION
