
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <fcntl.h>
#include <ctype.h>
int LINE_MAX = 512;
char error_message[30] = "An error has occurred\n";
void myPrint(char *msg) {
    write(STDOUT_FILENO, msg, strlen(msg));
}
int max_digits(long *arr, int arr_len) {
    int max_len = 0;
    for (int i = 0; i < arr_len; i++) {
        int digits = snprintf(NULL, 0, "%ld", arr[i]);
        if (digits > max_len)
            max_len = digits;
    }
    return max_len;
}
int built_ins(char *array[], int arr_len) {
    char cwd[LINE_MAX];
    if (array[1] != NULL && strcmp(array[1], ">") == 0) {
        write(STDOUT_FILENO, error_message, strlen(error_message));
        return 0;
    }
    if (strcmp(array[0], "pwd") == 0) {
        if(array[1] != NULL){
            write(STDOUT_FILENO, error_message, strlen(error_message));
            return 0; 
        }
        else{
        myPrint(getcwd(cwd, sizeof(cwd)));
        myPrint("\n");
        }
    } else if (strcmp(array[0], "exit") == 0) {
        if(arr_len > 1){
            write(STDOUT_FILENO, error_message, strlen(error_message));
            return 0;
        }
        return 1;
    } else if (strcmp(array[0], "cd") == 0) {
        if (arr_len == 1) {
            chdir(getenv("HOME"));
        } 
        else {
            char* directory = array[1];
            if (strcmp(array[1],"/") == 0 && arr_len > 2){
                write(STDOUT_FILENO, error_message, strlen(error_message));
            }
            if (chdir(directory) != 0){
                write(STDOUT_FILENO, error_message, strlen(error_message));
                return 0; 
            }
        }
    }
    return 0;
}
int is_builtin(char *inp) {
    char *builtins[] = {"cd", "pwd", "exit"};
    char *p = strtok(inp, " ");
    char *array[LINE_MAX];
    int i = 0; 
    while (p != NULL) {
        array[i] = p;
        p = strtok(NULL, " ");
        i++;
    }
    array[i] = NULL;
    for (int i = 0; i < 3; i++) {
        if (strcmp(builtins[i], array[0]) == 0) {
            return 1;
        }
    }
    return 0;
}
int is_empty_line(const char *line) {
    while (*line != '\0') {
        if (*line != ' ' && *line != '\t' && *line != '\n') {
            return 0;  // Line contains a character other than space, tab, or newline
        }
        line++;
    }
    return 1;  // Line consists only of space, tab, or newline characters
}
int read_input(char *pinput, char *file_dest) {
    int i = 0;
    int arr_len = 0;
    char *array[LINE_MAX];
    int fd = 0; 
    if(!(is_empty_line(pinput))){
        size_t input_len = strlen(pinput);
        for(int j = 0; j < input_len; j++){
        if (pinput[j] == '\t'){
            pinput[j] = ' ';
        }
    }
        
    if (input_len > 0 && (pinput[input_len - 1] == '\n' || pinput[input_len - 1] == '\t')) {
        pinput[input_len - 1] = '\0';
    }
    if(pinput[0] == '\t'){
        pinput[0] = ' ';
    }
    char *p = strtok(pinput, " ");
    while (p != NULL) {
        array[i] = p;
        p = strtok(NULL, " ");
        i++;
    }
    array[i] = NULL;
    arr_len = i;
    // builtins 
    if (is_builtin(pinput)) {
        if(file_dest != NULL){
             write(STDOUT_FILENO, error_message, strlen(error_message));
        }
        return built_ins(array, arr_len);
    } 
    // REDIRECTION
    int saved_stdout = dup(STDOUT_FILENO);   
    int file_descriptor;
    if(file_dest != NULL){
        while (*file_dest == ' ' || *file_dest == '\t') {
            file_dest++;
    }
        if ((file_descriptor = open(file_dest, O_CREAT | O_APPEND | O_WRONLY, 0600)) < 0) {
           
            write(STDOUT_FILENO, error_message, strlen(error_message));
            exit(1);
    }
        // Redirect stdout to file
        if (dup2(file_descriptor, STDOUT_FILENO) < 0) {
            write(STDOUT_FILENO, error_message, strlen(error_message));
            exit(3);
        }
        // Close the file descriptor as it's no longer needed
    }
        int pid = fork();
        if (pid < 0) {
            write(STDOUT_FILENO, error_message, strlen(error_message));
            exit(-1);
        } else if (pid == 0) {   // Child process
            // Redirect output if necessary
            execvp(array[0], array);
            write(STDOUT_FILENO, error_message, strlen(error_message));
            exit(1);
        } else { // Parent process
            // wait for child process to finish
            wait(NULL);
            if (dup2(STDOUT_FILENO, fd) < 0) {
                write(STDOUT_FILENO, error_message, strlen(error_message));
                exit(3);
            }
        }
        dup2(saved_stdout, STDOUT_FILENO);
        close(saved_stdout);
        close(file_descriptor);
    }
     return 0;
}
int colon_comm(char *pinput){
    char *copy = strdup(pinput);
    char *tok;
    char *tok_arr[514];
    int i = 0; 
    tok = strtok(copy, ";");
    while (tok != NULL) {
        tok_arr[i] = tok;
        tok = strtok(NULL, ";");
        i++; 
        }   
    
    for(int j = 0; j < i; j ++){
        if(read_input(tok_arr[j], NULL) == 1){
                return 1;
            };
        }
    free(copy);
    return 0; 
}
int redirection(char* line){
    char *file_dest = malloc(514);
    int start = 0;
    int end = strlen(line) - 1;
    while (isspace(line[start])) {
        start++;
    }
    while (end >= start && isspace(line[end])) {
        end--;
    }
    for (int j = start; j <= end; j++) {
        if (line[j] == '>') {
            strncpy(file_dest, line + j + 1, end - j);
            file_dest[end - j] = '\0'; 
            line[j] = '\0'; 
            break; 
        }
    }
    if (read_input(line, file_dest) == 1) {
        free(file_dest);
        return 1; 
    }
    free(file_dest); 
    return 0; 
}
int main(int argc, char *argv[]) {
    char cmd_new_strf[1000];
    char *pinput;
    FILE *fp;
    char *line = NULL; 
    size_t len = 0; 
    int size;    
   
    // batchfile
    if (argc > 1) {
        fp = fopen(argv[1], "r");
        if (fp == NULL) {
            write(STDOUT_FILENO, error_message, strlen(error_message));
        }
        fseek (fp, 0, SEEK_END);
        size = ftell(fp);
        if(size == 0){
            fclose(fp);
            exit(0);
        } 
        rewind(fp);
  
        while (getline(&line, &len, fp) != -1) {
            if (strlen(line) > LINE_MAX){
                myPrint(line);
                write(STDOUT_FILENO, error_message, strlen(error_message));
                continue; 
            }
            if (is_empty_line(line)){
                continue;
            }
    
            else{
                myPrint(line);
                if (strchr(line, ';') != NULL) {
                    if (colon_comm(line) == 1){
                        return 1; 
                    }
                } 
                
                // REDIRECTION
                else if(strchr(line, '>') != NULL){
                    if (strncmp (line,"pwd",3) == 0 || strncmp(line,"cd",2) == 0 || strncmp(line,"exit",4) == 0 ){
                        write(STDOUT_FILENO, error_message, strlen(error_message));
                        continue;
                    }
                  /*   if(is_builtin(line)){
                        write(STDOUT_FILENO, error_message, strlen(error_message));
                        continue; 
                    } */
                    if(redirection(line) == 1) return 1; 
                }
                else {
                    if(read_input(line, NULL) == 1){
                        return 1; 
                    }
                }
            }
        }
        free(line);
        fclose(fp);
    }
    while (1) {
        myPrint("myshell> ");
        pinput = fgets(cmd_new_strf, sizeof(cmd_new_strf), stdin);
        if (pinput == NULL) {
            // Error or end of file
            continue;
        }
        if(strlen(pinput) > LINE_MAX){
            write(STDOUT_FILENO, error_message, strlen(error_message));
            continue; 
        }
         if (strchr(pinput, ';') != NULL) {
            if (colon_comm(pinput) == 1) return 1;; 
        } 
        else {
            if (read_input(pinput, NULL) == 1) {
                return 1;
            }
        }
    }
    free(line); 
    return 0;
}
