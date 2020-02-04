/*
** EPITECH PROJECT, 2019
** env
** File description:
** hello
*/

#include <unistd.h>
#include <stdlib.h>
#include "my.h"

int my_env(int ac, char **av, lld_t *env)
{
    for (env = env->next; env; env = env->next)
        my_printf("%s\n", env->data);
    return (0);
}

int my_unsetenv(int ac, char **av, lld_t *env)
{
    char *str;
    for (int j = 1; j < ac; j++){
        str = av[j];
        char *reg_ex = my_strcat(str, "=*");
        for (int i = 0; i < (long int)env->data; i++){
            if (find_reg3(lld_read(env, i), reg_ex, 0, 0)){
                free(lld_pop(env, i));
                i--;
            }
        }
        free(reg_ex);
    }
    return (0);
}

int my_setenv(int ac, char **av, lld_t *env)
{
    if (ac == 2){
        char *av2[] = {0, av[1], ""};
        my_setenv(3, av2, env);
        return (0);
    }
    if (ac == 1) my_env(1, av, env);
    if (ac > 3) write(1, "setenv: Too many arguments.\n", 28);
    if (ac != 3) return (84);
    if (setenv_parse(av[1]))
        return (0);
    char *av2[] = {0, av[1], 0};
    my_unsetenv(2, av2, env);
    char *str = my_strcat(av[1], "=");
    lld_insert(env, (long)env->data, my_strcat(str, av[2]));
    free(str);
    return (0);
}

char *set_var(char *var, char *value, lld_t *env)
{
    if (!value || !var || !env) return (0);
    char *old = get_var(var, env);
    char *av[] = {0, var, 0};
    my_unsetenv(2, av, env);
    char *av1[] = {"", "", ""};
    av1[1] = var;
    av1[2] = value;
    my_setenv(3, av1, env);
    return (old);
}
