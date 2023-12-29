#define DLL_IMPLEMENTAION
#include "../../c/dll/dll.h"

int main(void) {
  DLL *dll = dll_new();
  if (dll == NULL) {
    fprintf(stderr, "ERROR: Linked List cant be initialized\n");
    return 1;
  }

  // dll_insert(dll, "Marvin", -1);
  // dll_insert(dll, "Lars", -1);
  // dll_insert(dll, "Bobo", -1);
  // dll_insert(dll, "HANS", -1);
  // dll_print(dll);

  // char *name = "Bobo";
  // if (dll_find(dll, name) != NULL) {
  //   printf("Found Bobo in Linked List\n");
  // }
  // if (dll_delete(dll, name)) {
  //   printf("Found %s in Linked List and deleted the Node.\n", name);
  // }
  // dll_print(dll);

  dll_insert(dll, "To Front", 0);
  dll_insert(dll, "To Last", -1);

  dll_insert(dll, "To HIGH", 107);
  printf("=============================================\n");
  dll_print(dll);
  printf("=============================================\n");

  dll_insert(dll, "To Second", 1);
  dll_insert(dll, "To trid", 3);

  printf("---------------------------------------------\n");
  dll_print(dll);
  printf("---------------------------------------------\n");

  dll_free(dll);

  return 0;
}
