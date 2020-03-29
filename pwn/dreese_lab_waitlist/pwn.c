#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define LINE_MAX 256
#define MAJOR_LEN 16
#define TIME_LEN 16
#define INSTRUCTOR_LEN 16
#define FLAG_SIZE 64

#define MAGIC_POSITION 3499

struct student {
  char *name;
  short waitlist_position;
  char major[MAJOR_LEN];
};

struct class_section {
 char time[TIME_LEN];
 char instructor[INSTRUCTOR_LEN];
};

struct student anon_student;
struct student *s;
int waitlist_size;

void get_off_the_waitlist() {
  // Get the flag from the file
  char flag[FLAG_SIZE];
  FILE *f = fopen("flag", "r");
  if (f == NULL) {
    printf("Couldn't open the flag, contact the admins.\n");
    exit(0);
  }

  if ((fgets(flag, FLAG_SIZE, f)) == NULL){
    puts("Couldn't read flag file, contact the admins.\n");
    exit(1);
  };

  if (s->waitlist_position != MAGIC_POSITION || strcmp(s->major, "CSE") != 0) {
    fprintf(stdout, "You must be waitlist position #%d, and a CSE major to get in the class! You are position: %d major: %s\n", MAGIC_POSITION, s->waitlist_position, s->major);
    return;
  }
  
  puts(flag);
  fclose(f);
}

void menu() {
  puts("Commands:");
  puts("\tlogin - login as a student");
  puts("\tget_off_the_waitlist - try to get off the waitlist for the flag");
  puts("\tlogout - log out");
  puts("\tquit - exit the program");
}
 
const char *get_studentname(struct student *st) {
  if (st->name == NULL) {
    return "anon";
  }
  else {
    return st->name;
  }
}

int login() {
  if (s != &anon_student) {
    printf("You must log out before you can log back in.\n");
    return -1; 
  }

  s = malloc(sizeof(struct student));
  int name_len;
  puts("Please enter the length of your name");
  scanf("%d", &name_len);
  getc(stdin);

  char *name = malloc(name_len+2);  // len + 2 allows for newline and null terminator
  s->name = name;

  puts("Please enter your name");
  if (fgets(name, name_len+2, stdin) == NULL) {
    puts("fgets failed");
    exit(-1);
  }

  char *end;
  if ((end=strchr(name, '\n')) != NULL) {
    end[0] = '\0';
  }
  
  return 0;
  
}

int logout() {
  char *name = s->name;
  if (s == &anon_student) {
    return -1;
  }
  else {
    free(s);
    free(name);
    s = &anon_student;
  }
  return 0;
}

struct class_section *read_class_section() {
  FILE *f = fopen("class_section.txt", "r");
  
  if (f) {
    char *end;
    
    struct class_section *section = malloc(sizeof(struct class_section));
    fgets(section->time, TIME_LEN, f);
    // Remove newline character
    if ((end=strchr(section->time, '\n')) != NULL) {
      end[0] = '\0';
    }

    fgets(section->instructor, INSTRUCTOR_LEN, f);
    // Remove newline character
    if ((end=strchr(section->instructor, '\n')) != NULL) {
      end[0] = '\0';
    }

    fclose(f);
    return section;
  }

  return NULL;
}

int main(int argc, char **argv) {

  setbuf(stdout, NULL);

  char buf[LINE_MAX];

  waitlist_size = rand() % 5000 + 3500;

  struct class_section *sec = read_class_section();
  if (!sec) {
    printf("Failed to load class section information. Contact admins.\n");
    return -1;
  }

  memset(anon_student.major, 0, MAJOR_LEN);
  anon_student.waitlist_position = 0;
  anon_student.name = NULL;

  s = &anon_student;
 
   
  puts("***************************************\n");
  puts("**     DREESE LAB WAITLIST SYSTEM    **\n");
  puts("***************************************\n");
  printf("You're viewing the waitlist for FLAG 1337.\n");
  printf("- %s (Instructor: %s). There are %d students on the waitlist.\n\n", sec->time, sec->instructor, waitlist_size);
  
  free(sec);

  menu();

  while(1) {
    puts("\nEnter your command:");
    fprintf(stdout, "[%s]> ", get_studentname(s));

    if(fgets(buf, LINE_MAX, stdin) == NULL)
      break;

    if (!strncmp(buf, "login", 5)){
      login();
    }
    else if(!strncmp(buf, "get_off_the_waitlist", 10)){
      get_off_the_waitlist();
    }
    else if(!strncmp(buf, "logout", 6)){
      logout();
    }
    else if(!strncmp(buf, "quit", 4)){
      return 0;
    }
    else{
      puts("Invalid option");
      menu();
    }
  }
}
