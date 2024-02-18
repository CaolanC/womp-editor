#include <ncurses.h>
#include <stdlib.h>
#include <threads.h>

typedef struct Line {
  int length;
  int capacity;
  char *content;
} Line;

Line makeLine() {
  Line line;
  line.length = 0;
  line.content = malloc(sizeof(char));
  line.capacity = 2;
  *(line.content)  = '\0';
  return line;
};

void reduceLine(Line* line, int reduction_size) {
  if (line -> length - reduction_size >= 1) {
    line -> content = realloc(line -> content, (line -> length - reduction_size) * sizeof(char));
  }
  line -> length -= reduction_size;
}

void extendLine(Line* line, int extension_size) {
  line -> content = realloc(line -> content, (extension_size + line -> length) * sizeof(char));
}

void append(Line *line, char input) {
  line -> content[line -> length] = input;
  if (line->length == line->capacity) {
    extendLine(line, line -> capacity * 2 - 2);
    line -> capacity = line -> capacity * 2 - 2;
  }
  line -> length++;
  line -> content[line -> length] = '\0';
}

int tryRemove(Line *line) {
  if (*(line -> content) == '\0') {
    return 0;
  };
  *(line -> content + line -> length - 1) = '\0';
  line -> length--;

  return 1;
}
