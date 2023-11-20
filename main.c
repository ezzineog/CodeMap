#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
// Colors - ANSI escape codes for changing the text color in the terminal.
const char *RESET = "\033[0m";
const char *BLACK = "\033[0;30m";
const char *RED = "\033[0;31m";
const char *GREEN = "\033[0;32m";
const char *YELLOW = "\033[0;33m";
const char *BLUE = "\033[0;34m";
const char *MAGENTA = "\033[0;35m";
const char *CYAN = "\033[0;36m";
const char *WHITE = "\033[0;37m";
const char *BOLD_BLACK = "\033[1;30m"; // bgs
const char *BOLD_RED = "\033[1;31m";
const char *BOLD_GREEN = "\033[1;32m";
const char *BOLD_YELLOW = "\033[1;33m";
const char *BOLD_BLUE = "\033[1;34m";
const char *BOLD_MAGENTA = "\033[1;35m";
const char *BOLD_CYAN = "\033[1;36m";
const char *BOLD_WHITE = "\033[1;37m";
const char *FONT_RESET = "\033[0m"; // Fonts
const char *FONT_BOLD = "\033[1m";
const char *FONT_DIM = "\033[2m";
const char *FONT_UNDERLINE = "\033[4m";
const char *FONT_BLINK = "\033[5m";
const char *FONT_REVERSE = "\033[7m";
const char *FONT_HIDDEN = "\033[8m";

const char *filters[] = {".", "..", ".git", ".env", ".gitignore", NULL};

void filter(const char *entry_name) {
  for (int i = 0; filters[i] != NULL; i++) {
    if (strcmp(entry_name, filters[i]) != 0) {
      continue;
    } else {
	printf("%sFiltredFile__%s__ \n%s", CYAN,entry_name, RESET);
    }
  }
}

void handle_sub(const char *path) {
  DIR *sub_dir;
  printf("handle sub =>  %s\n",path);
  struct dirent *entry;
  sub_dir = opendir(path); // Open sub directory
  if (sub_dir) {
    while ((entry = readdir(sub_dir)) != NULL) {
      filter(entry->d_name);
      printf("show ==>  %s  and %d\n", entry->d_name, DT_DIR);
      if (entry->d_type == DT_DIR) {
      	printf("\t+%s%s%s\n", BLUE, entry->d_name, RESET);
  	char sub_path[1560];
  	strcpy(sub_path, path);
  	strcat(sub_path, "/");
  	strcat(sub_path,entry->d_name);
  	printf("Sub path: %s\n", sub_path);
        handle_sub(sub_path); // Recursively call handle_sub() for subdirectories
      } else if (entry->d_type == DT_REG){
        printf("\t|%s\n", GREEN);
        printf("\t\n| ______%s%s\n", path, RESET);
      }
    }

    closedir(sub_dir);
  } else {
    printf("%sError opening subdirectory.\n%s%s%s", RED, FONT_BOLD, RESET, FONT_RESET);
  }
  printf(" |____________________________________________.%s%s\n", GREEN, RESET);
};

void listContents(char *folder_name) { // rint sub files and folders
  DIR *directory;
  struct dirent *entry;
  directory = opendir(folder_name); // Open the directory
  printf("list content func  => %s\n",folder_name);
  if (directory) {
    while ((entry = readdir(directory)) != NULL) {
      filter(entry->d_name);// Exclude "." and ".." entries/87408ik,8jm nn cx
      if (entry->d_type == DT_DIR) { // member access through pointer => in the context of C language. obj->key =>extract
        printf("+%s%s %s\n", BLUE, entry->d_name, RESET);
        handle_sub(folder_name);
      } else if (entry->d_type == DT_REG) {
        printf("%s%s%s\n", GREEN, entry->d_name, RESET);
      }
    }

    closedir(directory); // Close the directory like in python
  } else {
    printf("%sError opening the main directory.\n%s%s%s", RED, FONT_BOLD, RESET,FONT_RESET);
  }
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("%sPlease provide a %sfolder name%s as an argument%s. \n", YELLOW, FONT_BOLD, YELLOW, FONT_RESET);
    printf("Test 1 \n");
    return 1;
  }

  const char *folder_name = argv[1];
  printf("%s check 0 => %d %s %ld\n", MAGENTA, argc, getcwd("",200),__STDC_VERSION__);
  for (int i = 0; i < argc; i++) {
    printf("%s\t", argv[i]);
  }
  printf("%s\n",RESET);
  char folder_path[300];
  char cwd[270];
  realpath(".",cwd); 
  if(cwd == NULL) {
    printf("%sno such a current path !! %s",RED, RESET);
  }
  snprintf(folder_path, sizeof(folder_path), "%s/%s", cwd, folder_name);
  printf("%s main folder path =>  %s  \n%s",BLUE, folder_path, RESET);
  //listContents(folder_path);
  return 0;
}
