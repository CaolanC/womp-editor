#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <stdio.h>

#define EDITOR_NAME "WOMP WOMP"

#define STARTUP_ANIMATION_TIME (300000 / strlen(EDITOR_NAME))

typedef struct AsciiArtChar
{
  char character[64];
  int width;
} AsciiArtChar;

void readFileToString(FILE* f, WINDOW* window) {
  char buffer[100];
  int count = 1;
  wattron(window, COLOR_PAIR(rand() % 8));
  while(fgets(buffer, 100-1, f) != NULL) {
    wprintw(window, "%s", buffer);
    count++;
  }
  pclose(f);
}

int print_figlet(char chr, WINDOW* window)
{
  if (chr == ' ' || chr == '\n') {
    return 0;
  }
  char command[32] = "figlet -k ";
  int len = strlen(command);
  command[len] = chr;
  command[len+1] = '\0';
  FILE* file;
  file = popen(command, "r");
  if (file == NULL) {

    exit(1);
  }
  readFileToString(file, window);
  return 1;
};

typedef struct ScreenProperties
{
  int start_x, start_y;
  int rows, cols;
} ScreenProperties;

ScreenProperties getScreenProperties(WINDOW* window, int start_x, int start_y)
{
  ScreenProperties properties;
  getmaxyx(window, properties.rows, properties.cols);
  properties.start_x = start_x;
  properties.start_y = start_y;

  return properties;
}

void initCurses() {
  initscr();
  //raw();
  cbreak();
  keypad(stdscr, TRUE);
  noecho();

  if(has_colors() == FALSE) {
    endwin();
    printf("Dude your terminal doesn't support colour.\n It's effecfively mid.\n");
    exit(1);
  }
  use_default_colors();
  start_color();
  for(int i = 1; i < 8; i++) {
    init_pair(i, i, -1);
  }
}

WINDOW* create_window(uint height, uint width, uint start_x, uint start_y) {
  WINDOW* new_window = newwin(height, width, start_x, start_y);
  box(new_window, 0, 0);
  return new_window;
}

void destroy_window(WINDOW* window) {
  wborder(window, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
  wrefresh(window);
  delwin(window);
}

void startupRender(ScreenProperties main_screen) {
  usleep(STARTUP_ANIMATION_TIME);
  int color = rand() % 8;
  attron(COLOR_PAIR(color));
  mvaddch((int) main_screen.rows/2, ((int) main_screen.cols/2) - (int) strlen(EDITOR_NAME)/2, EDITOR_NAME[0]);
  for(int i = 1; i < strlen(EDITOR_NAME); i++) {
    usleep(STARTUP_ANIMATION_TIME);

    attron(COLOR_PAIR(color));
    if (EDITOR_NAME[i] == ' ') {
      color = rand() % 8;
    }
    addch(EDITOR_NAME[i]);
    refresh();
  }
  curs_set(0);
  usleep(1000000);
  clear();
}

void renderBigLetter(uint letter_index, ScreenProperties main_screen, int v_center, int spacing)
{
  WINDOW* temp_letter_window = create_window((int) main_screen.rows / 2, spacing, v_center, spacing*letter_index+1);
  wborder(temp_letter_window, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
  print_figlet(EDITOR_NAME[letter_index], temp_letter_window);
  wrefresh(temp_letter_window);
}

void startupRenderBig(ScreenProperties main_screen) {

  int v_center = (int) main_screen.rows / 2.5;
  int spacing = (int) main_screen.cols / strlen(EDITOR_NAME);


  usleep(STARTUP_ANIMATION_TIME);
  move((int) main_screen.rows/2, ((int) main_screen.cols/2) - (int) strlen(EDITOR_NAME)/2);
  for(int i = 0; i < strlen(EDITOR_NAME); i++) {
    renderBigLetter(i, main_screen, v_center, spacing);
    usleep(STARTUP_ANIMATION_TIME);
  }
  curs_set(0);
  usleep(200000);
  //sleep(10);
  clear();
}


void startRender() {
  ScreenProperties main_screen_prop = getScreenProperties(stdscr, 0, 0);
  startupRenderBig(main_screen_prop);
  refresh();
  WINDOW* editor_window = create_window(main_screen_prop.rows, main_screen_prop.cols, 0, 0);
  keypad(editor_window, TRUE);
  ScreenProperties editor_window_prop = getScreenProperties(editor_window, 1, 1);
  wborder(editor_window, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
  wrefresh(editor_window);
  int chr = wgetch(editor_window);
  int cursor_x = 0;
  int cursor_y = 0;
  curs_set(1);
  while (chr != (int) 'q') {
    switch(chr)
    {
      case KEY_RIGHT:
        getyx(editor_window, cursor_y, cursor_x);
        wmove(editor_window, cursor_y, cursor_x+1);
        cursor_x++;
        break;

      case KEY_LEFT:
        getyx(editor_window, cursor_y, cursor_x);
        wmove(editor_window, cursor_y, cursor_x-1);
        cursor_x--;
        break;


      case KEY_UP:
        getyx(editor_window, cursor_y, cursor_x);
        wmove(editor_window, cursor_y-1, cursor_x);
        cursor_y++;
        break;

      case KEY_DOWN:
        getyx(editor_window, cursor_y, cursor_x);
        wmove(editor_window, cursor_y+1, cursor_x);
        cursor_y--;
        break;

      case KEY_BACKSPACE:
        wmove(editor_window, cursor_y, cursor_x-1);
        wdelch(editor_window);
        cursor_x--;
        break;

      default:
        waddch(editor_window, chr);
        cursor_x++;
    } 
    wrefresh(editor_window);
    chr = wgetch(editor_window);
  };
  endwin();
} 



int main(int arc, char* argv[]) {
  time_t t1;
  srand(time(&t1));
  initCurses();
  startRender();
  int max_value;
  
}
