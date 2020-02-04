/*
** EPITECH PROJECT, 2019
** trash
** File description:
** hello
*/

#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include "my.h"

int my_cd_nd(char **av, lld_t *env, char *newpwd)
{
    DIR *folder;
    if (!(folder = opendir(newpwd))){
        write(2, av[1], my_strlen(av[1]));
        char *str_e = strerror(errno);
        write(2, ": ", 2), write(2, str_e, my_strlen(str_e));
        write(2, ".\n", 2);
        free(newpwd);
        return ((84 << 8));
    }
    char *pwd_t = getpwd();
    free(set_var("OLDPWD", pwd_t, env)), closedir(folder), chdir(newpwd);
    free(pwd_t), pwd_t = getpwd(), free(set_var("PWD", pwd_t, env));
    free(pwd_t), free(newpwd);
    return (0);
}

int my_cd(int ac, char **av, lld_t *env)
{
    if (ac > 2){
        write(2, "cd: Too many arguments.\n", 24);
        return ((84 << 8));
    }
    char *newpwd = 0;
    if (ac == 2 && !my_strcmp(av[1], "-")){
        newpwd = get_var("OLDPWD", env);
        if (!newpwd) return (0);
    } else if (ac == 2){
        char *pwd = getpwd();
        newpwd = my_strcat(pwd, av[1]);
        free(pwd);
    } else
        for (newpwd = getpwd(); my_strcmp(newpwd, "//"); ){
            char *newpwd2 = my_strcat(newpwd, "..");
            free(newpwd), chdir(newpwd2), free(newpwd2), newpwd = getpwd();
        }
    return (my_cd_nd(av, env, newpwd));
}

int my_exit_nd(char **av, int good, int ret)
{
    for (int i = 0; av[1][i]; i++)
        if (av[1][i] < '0' || av[1][i] > '9') good = 0;
    if (my_getnbr(av[1]) != 0 && !good){
        write(2, "exit: Badly formed number.\n", 27);
        return (0);
    }
    if (!good){
        write(2, "exit: Expression Syntax.\n", 25);
        return (0);
    }
    return (1);
}

int my_exit(int ac, char **av, lld_t *env)
{
    if (ac > 2){
        write(2, "exit: Expression Syntax.\n", 25);
        return (0);
    }
    int good = 1;
    int ret = 0;
    if (ac == 2){
        if (!my_exit_nd(av, good, ret))
            return (0);
        ret = my_getnbr(av[1]);
    }
    while ((long int)env->data) free(lld_pop(env, 0));
    lld_free(env), isatty(0) ? my_printf("exit\n") : 0;
    av ? free(av[0]), free(av) : 0;
    if (ac <= 0)
        exit(-ac);
    exit(ret);
}
