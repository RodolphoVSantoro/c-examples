// typedef char *str;
// #define VEC_TYPE str
// #define SHOULD_FREE_TYPE 1
// #include <stdlib.h>
// void str_dealloc(char *i) { free(i); }

/*
 * VEC_TYPE is the type of the vector
 * SHOULD_FREE_TYPE is a boolean value that determines if the vector should free
 * Defines a vec type and functions for that type
 * If SHOULD_FREE_TYPE is 1, then the vector will free the data it contains when
 * free is called. For this to work, the type must have a dealloc function
 */

#ifndef VEC_TYPE
#error "VEC_TYPE must be defined before including vec.h"
#endif

#ifndef SHOULD_FREE_TYPE
#error "SHOULD_FREE_TYPE must be defined before including vec.h"
#endif

#include "err.h"
#include "macros.h"

#define STRUCT_NAME(x) CONCAT2(x, _VEC)
#define TYPE_NAME(x) CONCAT2(x, _vec)
typedef struct STRUCT_NAME(VEC_TYPE) {
  VEC_TYPE *data;
  int size;
  int capacity;
} TYPE_NAME(VEC_TYPE);

/*
 * User should define a dealloc function for the type
 * If SHOULD_FREE_TYPE is 1, then the vector will free the data it contains when
 * - free is called
 * - set is called on an element before it is overwritten
 * - reset is called
 */
#define DEALLOC_DEF(x) CONCAT2(x, _dealloc)

#define NEW_DEF(x) CONCAT3(x, _vec, _new)
TYPE_NAME(VEC_TYPE) * NEW_DEF(VEC_TYPE)(void) {
  TYPE_NAME(VEC_TYPE) *vec =
      (TYPE_NAME(VEC_TYPE) *)malloc(sizeof(TYPE_NAME(VEC_TYPE)));
  vec->data = (VEC_TYPE *)malloc(sizeof(VEC_TYPE));
  vec->size = 0;
  vec->capacity = 1;
  return vec;
}

#define PUSH_DEF(x) CONCAT3(x, _vec, _push)
void PUSH_DEF(VEC_TYPE)(TYPE_NAME(VEC_TYPE) * vec, VEC_TYPE c) {
  int new_capacity = vec->capacity;
  if (vec->size >= vec->capacity) {
    new_capacity *= 2;
    vec->data = (VEC_TYPE *)realloc(vec->data, new_capacity * sizeof(VEC_TYPE));
  }
  if (vec->data == NULL) {
    printerrf("Error increasing vec from %d to %d\n", vec->capacity,
              vec->capacity * 2);
    exit(1);
  }
  vec->capacity = new_capacity;
  vec->data[vec->size] = c;
  vec->size++;
}

#define POP_DEF(x) CONCAT3(x, _vec, _pop)
VEC_TYPE POP_DEF(VEC_TYPE)(TYPE_NAME(VEC_TYPE) * vec) {
  if (vec->size == 0) {
    printerrf("Error popping empty vec\n");
    exit(1);
  }
  vec->size--;
  return vec->data[vec->size];
}

#define GET_DEF(x) CONCAT3(x, _vec, _get)
VEC_TYPE GET_DEF(VEC_TYPE)(TYPE_NAME(VEC_TYPE) * vec, int index) {
  if (index >= vec->size || index < 0) {
    printerrf("Error getting index %d from char vec of size %d\n", index,
              vec->size);
    exit(1);
  }
  return vec->data[index];
}

#define SET_DEF(x) CONCAT3(x, _vec, _set)
void SET_DEF(VEC_TYPE)(TYPE_NAME(VEC_TYPE) * vec, int index) {
  if (index >= vec->size || index < 0) {
    printerrf("Error setting index %d in char vec of size %d\n", index,
              vec->size);
    exit(1);
  }
#if SHOULD_FREE_TYPE == 1
  DEALLOC_DEF(VEC_TYPE)(vec->data[index]);
#endif
}

#define RESIZE_DEF(x) CONCAT3(x, _vec, _resize)
void RESIZE_DEF(VEC_TYPE)(TYPE_NAME(VEC_TYPE) * vec, int capacity) {
  if (capacity == 0) {
    printerrf("Error cant resize vec to 0(use reset)\n");
    exit(1);
  }
  vec->data = (VEC_TYPE *)realloc(vec->data, capacity * sizeof(VEC_TYPE));
  if (vec->data == NULL) {
    printerrf("Error resizing vec\n");
    exit(1);
  }
  if (capacity > vec->capacity) {
    for (int i = vec->capacity; i < capacity; i++) {
      vec->data[i] = 0;
    }
  }
  vec->capacity = capacity;
}

#define RESET_DEF(x) CONCAT3(x, _vec, _reset)
/*
 * A call to reset will set the size of the vector to 0 and the capacity to 1.
 * this may cause leaks if the vector contains pointers to heap memory,
 * and you do not have other references to that memory
 */
void RESET_DEF(VEC_TYPE)(TYPE_NAME(VEC_TYPE) * vec) {
#if SHOULD_FREE_TYPE == 1
  for (int i = 0; i < vec->size; i++) {
    DEALLOC_DEF(VEC_TYPE)(vec->data[i]);
  }
#endif
  vec->size = 0;
  vec->capacity = 1;
}

#define LEN_DEF(x) CONCAT3(x, _vec, _len)
int LEN_DEF(VEC_TYPE)(TYPE_NAME(VEC_TYPE) * vec) { return vec->size; }

#define FREE_DEF(x) CONCAT3(x, _vec, _dealloc)
void FREE_DEF(VEC_TYPE)(TYPE_NAME(VEC_TYPE) * *vec) {
#if SHOULD_FREE_TYPE == 1
  for (int i = 0; i < LEN_DEF(VEC_TYPE)(*vec); i++) {
    DEALLOC_DEF(VEC_TYPE)((*vec)->data[i]);
  }
#endif
  free((*vec)->data);
  (*vec)->data = NULL;
  free((*vec));
  *vec = NULL;
}

#undef VEC_TYPE
#undef SHOULD_FREE_TYPE

#undef STRUCT_NAME
#undef TYPE_NAME

#undef NEW_DEF
#undef PUSH_DEF
#undef POP_DEF
#undef GET_DEF
#undef RESIZE_DEF
#undef RESET_DEF
#undef LEN_DEF
#undef FREE_DEF
#undef DEALLOC_DEF
