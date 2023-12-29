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
int dll_push_front(DLL *dll, char *item);
int dll_push_back(DLL *dll, char *item);
int dll_pop_front(DLL *dll);
int dll_pop_back(DLL *dll);

int dll_delete(DLL *dll, char *item);
int dll_insert(DLL *dll, char *item, int pos);

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

int dll_push_front(DLL *dll, char *item) { return dll_insert(dll, item, 0); }

int dll_push_back(DLL *dll, char *item) { return dll_insert(dll, item, -1); }

int dll_pop_back(DLL *dll) {
  NODE *item_node = dll->tail->prev;
  if (dll->head->next == dll->tail) {
    return 0;
  }

  dll->tail->prev->prev->next = dll->tail;
  // item_node->prev->next = dll->tail;
  dll->tail->prev = dll->tail->prev->prev;
  // dll->tail->prev = item_node->prev;
  free(item_node);
  return 1;
}

int dll_pop_front(DLL *dll) {
  NODE *item_node = dll->head->next;
  if (dll->head->next == dll->tail) {
    return 0;
  }

  dll->head->next->next->prev = dll->head;
  // item_node->next->prev = dll->head;
  dll->head->next = dll->head->next->next;
  // dll->head = item_node->next;
  free(item_node);
  return 1;
}

int dll_insert(DLL *dll, char *item, int pos) {
  NODE *new_node = (NODE *)calloc(1, sizeof(NODE));
  NODE *temp = (NODE *)calloc(1, sizeof(NODE));
  if (new_node == NULL || temp == NULL) {
    fprintf(stderr, "The allocation of a new node faild with : %s\n",
            strerror(errno));
    return 1;
  }

  new_node->item = item;

  // At the 0 Element
  temp = dll->head->next;
  if (pos == 0) {
    new_node->next = dll->head->next;
    new_node->prev = dll->head;
    dll->head->next->prev = new_node;
    dll->head->next = new_node;
  } else if (pos < 0) {
  pushback:
    new_node->next = dll->tail;
    new_node->prev = dll->tail->prev;
    dll->tail->prev->next = new_node;
    dll->tail->prev = new_node;
  } else {
    for (int i = 0; i < pos; ++i) {
      if (temp == dll->tail) {
        goto pushback;
      }
      temp = temp->next;
    }

    new_node->next = temp;
    new_node->prev = temp->prev;
    temp->prev->next = new_node;
    temp->prev = new_node;
  }

  temp = NULL;
  free(temp);
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
