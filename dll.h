// A dynamic double linked list header only library
// Copyright © 2024 Marvin Frohwitter

// Permission is hereby granted, free of charge, to any person obtaining
// a copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
// OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
// OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


#ifndef DLL_H_
#define DLL_H_
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef DLLDEF
#define DLLDEF static inline
#endif // DLLDEF

typedef struct NODE {
  char *item;
  struct NODE *next;
  struct NODE *prev;

} NODE;

typedef struct DLL DLL;

#ifdef DLL_IMPLEMENTATION
struct DLL {
  NODE *head;
  NODE *tail;
};
#endif // DLL_IMPLEMENTATION

DLLDEF DLL *dll_new();
DLLDEF int dll_push_front(DLL *dll, char *item);
DLLDEF int dll_push_back(DLL *dll, char *item);
DLLDEF int dll_pop_front(DLL *dll);
DLLDEF int dll_pop_back(DLL *dll);

DLLDEF void dll_clear(DLL *dll);
DLLDEF int dll_delete(DLL *dll, char *item);
DLLDEF int dll_insert(DLL *dll, char *item, int pos);

DLLDEF NODE *dll_find(DLL *dll, char *needle);
DLLDEF char *dll_print_cstr(char *buf, DLL *dll);
DLLDEF void dll_print(FILE *__restrict __stream, DLL *dll);
DLLDEF void dll_print_full(FILE *__restrict __stream, DLL *dll);
DLLDEF void dll_free(DLL *dll);

#endif // DLL_H_

#ifdef DLL_IMPLEMENTATION

DLLDEF void dll_clear(DLL *dll) {
  dll->head->next = dll->tail;
  dll->head->prev = dll->tail;
  dll->tail->prev = dll->head;
  dll->tail->next = dll->head;
}

DLLDEF DLL *dll_new() {

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

DLLDEF int dll_push_front(DLL *dll, char *item) {
  return dll_insert(dll, item, 0);
}

DLLDEF int dll_push_back(DLL *dll, char *item) {
  return dll_insert(dll, item, -1);
}

DLLDEF int dll_pop_back(DLL *dll) {
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

DLLDEF int dll_pop_front(DLL *dll) {
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

DLLDEF int dll_insert(DLL *dll, char *item, int pos) {
  size_t n = strlen(item);
  NODE *new_node = (NODE *)calloc(1, sizeof(NODE));
  new_node->item = malloc(n + 1);

  NODE *temp = (NODE *)calloc(1, sizeof(NODE));
  if (new_node == NULL || temp == NULL) {
    fprintf(stderr, "The allocation of a new node faild with : %s\n",
            strerror(errno));
    return 0;
  }

  new_node->item = memcpy(new_node->item, item, n);
  // new_node->item  = item;

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
  return 1;
}

DLLDEF int dll_delete(DLL *dll, char *item) {
  NODE *item_node = dll_find(dll, item);
  if (item_node == NULL) {
    return 0;
  }
  item_node->prev->next = item_node->next;
  item_node->next->prev = item_node->prev;
  free(item_node);

  return 1;
}

DLLDEF NODE *dll_find(DLL *dll, char *needle) {
  NODE *temp = dll->head->next;
  while (temp != dll->tail) {
    if (strcmp(needle, temp->item) == 0)
      return temp;
    temp = temp->next;
  }

  return NULL;
}

DLLDEF char *dll_print_cstr(char *buf, DLL *dll) {
  NODE *temp = dll->head->next;

  if (temp != dll->tail) {
    strcat(buf, temp->item);
    temp = temp->next;
  }

  while (temp != dll->tail) {
    strcat(buf, ", ");
    strcat(buf, temp->item);
    temp = temp->next;
  }

  return buf;
}

DLLDEF void dll_print(FILE *__restrict __stream, DLL *dll) {
  NODE *temp = dll->head->next;

  if (temp != dll->tail) {
    fprintf(__stream, "%s", temp->item);
    temp = temp->next;
  }

  while (temp != dll->tail) {
    fprintf(__stream, ", %s", temp->item);
    temp = temp->next;
  }
}

DLLDEF void dll_print_full(FILE *__restrict __stream, DLL *dll) {
  NODE *temp = dll->head->next;
  int i = 1;
  while (temp != dll->tail) {
    fprintf(__stream, "Item%d: %s\n", i, temp->item);
    ++i;
    temp = temp->next;
  }
}

DLLDEF void dll_free(DLL *dll) {
  free(dll->head);
  free(dll->tail);
  free(dll);
}

#endif // DLL_IMPLEMENTATION
