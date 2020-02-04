/*
** EPITECH PROJECT, 2019
** init
** File description:
** hello
*/

#include <stdlib.h>
#include "my.h"

lld_t *words_to_lld(char **words)
{
    lld_t *env = lld_init();
    for (int i = 0; words[i]; i++){
        lld_insert(env, (long int)env->data, my_strdup(words[i]));
    }
    return (env);
}

char **build_env(lld_t *env)
{
    char **newenv = malloc(sizeof(char *) * ((long int)env->data + 1));
    int i = 0;
    for (env = env->next; env; env = env->next, i++){
        newenv[i] = my_strdup(env->data);
    }
    newenv[i] = 0;
    return (newenv);
}
