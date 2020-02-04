/*
** EPITECH PROJECT, 2019
** exec
** File description:
** hello
*/

#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include "my.h"

int my_point_slash(int ac, char **av, lld_t *env)
{
    int stat = 0;
    char **env2 = build_env(env);
    int pid = 0;
    char *av2[] = {av[0], av[1], 0};
    if ((pid = fork()) == 0){
        if (execve(av[0], av2, env2)){
            write(2, av[0], my_strlen(av[0]));
            write(2, ": Command not found.\n", 21), stat = 1;
            exit(0);
        }
    }
    waitpid(pid, &stat, 0);
    for (int i = 0; env2[i]; i++) free(env2[i]);
        free(env2);
    return (stat);
}

int my_other(int ac, char **av, lld_t *env)
{
    char *path = get_var("PATH", env); if (!path) return (84);
    char **path_word = my_str_to_word_array(path, ':');
    char *com = my_strcat("/", av[0]);
    char *str = 0;
    int stat = -1;
    int pid;
    for (int i = 0; path_word[i]; i++, free(str)){
        str = my_strcat(path_word[i], com);
        if (!access(str, X_OK)){
            char **env2 = build_env(env);
            if (!(pid = fork())) execve(str, av, env2), exit(0);
            waitpid(pid, &stat, 0);
            for (int i = 0; env2[i]; i++) free(env2[i]); free(env2), free(str);
            break;
        }
    }
    if (stat == -1) write(2, av[0], my_strlen(av[0])),
        write(2, ": Command not found.\n", 21), stat = 1;
    free(com), free(path_word[0]), free(path_word), free(path);
    return (stat);
}
