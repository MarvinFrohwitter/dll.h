#define DLL_IMPLEMENTAION
#include "../../c/dll/dll.h"

int main(void) {
  DLL *dll = dll_new();
  if (dll == NULL) {
    fprintf(stderr, "ERROR: Linked List cant be initialized\n");
    return 1;
  }

  dll_insert(dll, "Marvin");
  dll_insert(dll, "Lars");
  dll_insert(dll, "Bobo");
  dll_insert(dll, "HANS");
  dll_print(dll);

  char *name = "Bobo";
  if (dll_find(dll, name) != NULL) {
    printf("Found Bobo in Linked List\n");
  }
  if (dll_delete(dll, name)) {
    printf("Found %s in Linked List and deleted the Node.\n", name);
  }
  dll_print(dll);

  dll_free(dll);

  return 0;
}
