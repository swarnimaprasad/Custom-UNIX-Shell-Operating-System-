


#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
void print_array_of_pointers(char *array[], int size) {
  for (int i = 0; i < size; i++) {
    printf("The address of element %d is %s\n", i, array[i]);
  }
}


void split(const char *str, char delimiter, char *arguments[5]) {
    char *token = strtok((char *)str, &delimiter);
    int index = 0;
    while (token != NULL) {
        arguments[index] = token;
        index++;
        token = strtok(NULL, &delimiter);
    }
    arguments[index] = NULL; // Terminate the array with a NULL pointer
}

int countStrings(char **array) {
    int count = 0;
    while (array[count] != NULL) {
        count++;
    }
    return count;
}
void replace_newlines(char *arguments[], int size) {
  for (int i = 0; i < size; i++) {
    char *argument = arguments[i];
    int len = strlen(argument);
    if (argument[len - 1] == '\n') {
      argument[len - 1] = '\0';
    }
  }
}


void word(int argcount, char *argarray[]) {
    if (argcount < 2 || argcount > 4) {
        printf("give the correct argument");
        return;
    }

    bool n = false;
    bool d = false;
    char *file1 = argarray[1];
    char *file2 = NULL;

    if (argcount == 2) {
        n = true;
        file1 = argarray[1];
    } else {
        if (strcmp(argarray[1], "-n") == 0) {
            n = true;
        } 
        else if (strcmp(argarray[1], "-d") == 0) {
            d = true;
        }
        file1 = argarray[2]; // Moved this line to here
    }

    if (argcount == 4) {
        file2 = argarray[3];
    }

    FILE *f1 = fopen(file1, "r");
    if (f1 == NULL) {
        printf("Error: File %s does not exist.\n", file1);
        return;
    }

    int count1 = 0;
    bool inWord1 = false;
    bool chk = false;
    char ch;

    while ((ch = getc(f1)) != EOF) {
        if (n) {
            if (ch == ' ' || ch == '\t' || (ch == '\n' && chk)) {
                inWord1 = false;
                if (ch == '\n') {
                    chk = false;
                }
            } else if (!inWord1) {
                inWord1 = true;
                count1++;
            }
            if (ch == '\n') {
                chk = true;
            }
        } else if (d) {
            if (ch == ' ' || ch == '\t' || ch == '\n') {
                inWord1 = false;
            } else if (!inWord1) {
                inWord1 = true;
                count1++;
            }
        }
    }

    fclose(f1);

    if (d && file2 == NULL) {
        printf("Error: -d option requires two file names.\n");
        return;
    }

    if (file2 != NULL) {
        FILE *f2 = fopen(file2, "r");
        if (f2 == NULL) {
            printf("Error: File %s does not exist.\n", file2);
            return;
        }

        int count2 = 0;
        bool inWord2 = false;

        while ((ch = getc(f2)) != EOF) {
            if (ch == ' ' || ch == '\t' || ch == '\n') {
                inWord2 = false;
            } else if (!inWord2) {
                inWord2 = true;
                count2++;
            }
        }

        fclose(f2);
        int diff = abs(count1 - count2);
        printf("Difference in word sizes: %d\n", diff);
    } else {
        printf("Number of words: %d\n", count1);
    }
}

int main() {
    while (1) {
        char *arguments[5]; // Keep this size unchanged
        char command[150];
        printf("1 word\n2 dir\n3 date\n4 exit\n");
        fgets(command, 150, stdin);
        split(command,' ', arguments);
        int ch;
        int count = countStrings(arguments);
        replace_newlines(arguments,count);
        if (strcmp(arguments[0], "word") == 0) {
            word(count, arguments);
        } else if(strcmp(arguments[0], "dir") == 0) {
            pid_t ppid = getpid();
            pid_t pid = fork();

            if (pid < 0) {
                printf("Fork failed.\n");
            } 
            else if (pid == 0) {
                execvp("./dir", arguments);
                perror("execvp"); // Print error message if execvp fails
                exit(1);
            } 
            else {
                ppid = getpid();
                wait(NULL);
            }
        } else if (strcmp(arguments[0], "date") == 0){
            pid_t ppid = getpid();
            pid_t pid = fork();

            if (pid < 0) {
                printf("Fork failed.\n");
            } else if (pid == 0) {
                execvp("./date", arguments);
                perror("execvp"); // Print error message if execvp fails
                exit(1);
            } else {
                ppid = getpid();
                wait(NULL);
            }
            
        }
        else if((strcmp(arguments[0], "exit") == 0)){
            break;

        }
    }

    return 0;
}

