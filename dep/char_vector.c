#include <stdlib.h>
#include <stdio.h>

typedef struct Vector
{
  int size;
  void** array;
} Vector;

Vector newVector() {
  void** ptr = calloc(0, sizeof(void*));
  Vector vec;
  vec.size = 0;
  vec.array = ptr;
  return vec;
};

int capacityGivenSize(Vector* vector) {
  if (vector -> size > 1) {
    return (vector -> size * 2 - 2); 
  };

  return vector -> size + 1;
}

void resize(Vector* vector) {
  int new_size = capacityGivenSize(vector);
  int* ptr = realloc(vector -> array, new_size);
  vector -> size = new_size;
}
void pushBackVector(Vector* vector, void* value) {
  resize(vector);
  void* ptr_value = value;
  // DEREFERENCE
  *(vector->array + vector->size) = ptr_value;
}

int main() {
  Vector vec = newVector();
  int a = 12;
  int* b = &a;
  pushBackVector(&vec, b);
  for(int i = 0; i < vec.size; i++) {
    int* a = (int*) vec.array+i;
    printf("%d\n", *a);
  }
  printf("----\n");
  for(int i = 0; i <= vec.size; i++) {
    int* c = (int*) vec.array+i;
    printf("%d\n", *c);
  }
}
