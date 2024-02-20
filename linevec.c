#ifndef LINE__H 
  #include "line.c"
#endif /* ifndef LINE */

typedef struct LineVec {
  int length;
  Line** content;
} LineVec;

LineVec makeLineVec() {
  LineVec vec;
  vec.length = 0;
  vec.content = malloc(sizeof(Line));
  return vec;
}

void extendLineVec(LineVec* vec, int extension_size) {
  vec -> content = realloc(vec -> content, (extension_size + vec -> length) * sizeof(Line));
}

void appendLineVec(LineVec* vec, Line* input) {
  vec -> content[vec -> length] = input;
  extendLineVec(vec, 1);
  vec -> length++;
}

void printLineVec(LineVec vec) {
  for(int i = 0; i < vec.length; i++) {
  }
}

int tryRemoveVec(Line *line) {
  if (line -> length == 0) {
    return 0;
  };

  if (line -> length == (int) (line -> capacity + 2) / 2 && line -> length > 2) {
    line -> content = realloc(line -> content, (line -> length - 1) * sizeof(Line));
    line -> capacity = line -> length;
  }

  *(line -> content + line -> length - 1) = '\0';
  line -> length--;

  return 1;
}

