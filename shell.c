#include "shell.h"

command* create_command(int argc) {
    command* rv = (command*)malloc(sizeof(command));
    rv->argv = (char**)malloc((argc + 1) * sizeof(char*));
    rv->argc = argc;
    for (int i = 0; i < argc; i++) {
        rv->argv[i] = (char*)malloc(MAX_ARG_LEN);
    }
    rv->argv[argc] = NULL;
    return rv;
}

command* parse(char* line) {
    int i = 0;
    char* clone = (char*)malloc(strlen(line) + 1);
    strcpy(clone, line);
    char* tok = strtok(clone, " ");
    while (tok != NULL) {
        i++;
        tok = strtok(NULL, " ");
    }
    free(clone);
    command* rv = create_command(i);
    rv->argc = i;
    clone = strdup(line);
    tok = strtok(clone, " ");
    i = 0;
    while (tok != NULL) {
        strcpy(rv->argv[i], tok);
        i++;
        tok = strtok(NULL, " ");
    }
    free(clone);
    return rv;
}

bool find_full_path(command* cmd) {
    char* path = (char*)malloc(MAX_ENV_VAR_LEN);
    strcpy(path, getenv("PATH"));
    char* tok = strtok(path, ":");
    struct stat sb;
    while (tok != NULL) {
        char* path_appended = (char*)malloc(MAX_ENV_VAR_LEN);
        strcpy(path_appended, tok);
        strcat(path_appended, "/");
        strcat(path_appended, cmd->argv[0]);
        if (stat(path_appended, &sb) == 0 && S_ISREG(sb.st_mode)) {
            free(cmd->argv[0]);
            cmd->argv[0] = strdup(path_appended);
            free(path);
            free(path_appended);
            return true;
        }
        free(path_appended);
        tok = strtok(NULL, ":");
    }
    free(path);
    return false;
}

int execute(command* cmd) {
    if (is_builtin(cmd)) {
        do_builtin(cmd);
        return SUCCESS;
    } else if (find_full_path(cmd)) {
        pid_t pid = fork();
        if (pid == 0) {
            execv(cmd->argv[0], cmd->argv);
            cleanup(cmd);
            return ERROR;
        } else {
            int exit_status;
            wait(&exit_status);
            return ERROR;
        }
        return SUCCESS;
    } else {
        printf("Command %s not found!\n", cmd->argv[0]);
        return ERROR;
    }
}

void cleanup(command* cmd) {
    int i = 0;
    while (i < cmd->argc) {
        free(cmd->argv[i]);
        i++;
    }
    free(cmd->argv);
    free(cmd);
}

bool is_builtin(command* cmd) {
    // Do not modify
    char* executable = cmd->argv[0];
    if (strcmp(executable, "cd") == 0 || strcmp(executable, "exit") == 0)
        return true;
    return false;
}

int do_builtin(command* cmd) {
    // Do not modify
    if (strcmp(cmd->argv[0], "exit") == 0) exit(SUCCESS);

    // cd
    if (cmd->argc == 1)
        return chdir(getenv("HOME"));  // cd with no arguments
    else if (cmd->argc == 2)
        return chdir(cmd->argv[1]);  // cd with 1 arg
    else {
        fprintf(stderr, "cd: Too many arguments\n");
        return ERROR;
    }
}
