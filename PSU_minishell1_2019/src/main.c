/*
** EPITECH PROJECT, 2019
** main
** File description:
** hello
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "my.h"

const com_t coms[] =
{
    {my_cd, "cd"},
    {my_env, "env"},
    {my_setenv, "setenv"},
    {my_unsetenv, "unsetenv"},
    {my_exit, "exit"},
    {my_point_slash, "./*"},
    {my_other, "*"},
    {0, 0}
};

int scan_com(char *line, lld_t *env)
{
    char **words = parsing_a(line);
    if (!words) write(2, "Unmatched '\"'.\n", 16);
    if (!words) return (0);
    free(line);
    int words_nb = 0;
    int ret = -1;
    for (; words[words_nb]; words_nb++);
    for (int i = 0; coms[i].exe; i++){
        if (find_reg3(words[0], coms[i].name, 0, 0)){
            int val = coms[i].exe(words_nb, words, env);
            char *str_e = strsignal(val & 0x7F);
            if (val & 128) write(2, str_e, my_strlen(str_e)), write(2, "\n", 1);
            isatty(0) ? my_printf("%d ", val >> 8) : 0;
            ret = val >> 8;
            break;
        }
    }
    free(words[0]), free(words);
    return (ret);
}

int main(int ac, char **av, char **env)
{
    lld_t *lld_env = words_to_lld(env);
    int ret = 0;
    size_t zero = 0;
    int go = 1;
    while (go){
        char *pwd = getpwd();
        isatty(0) ? my_printf("%s> ", pwd) : 0;
        free(pwd);
        char *line = 0;
        int size = 0;
        size = getline(&line, &zero, stdin);
        if (size == -1) break;
        if (line[size-1] != '\n')
            go = 0, line[size] = 0;
        else
            line[size-1] = 0;
        ret = scan_com(line, lld_env);
    }
    my_exit(-ret, 0, lld_env);
    return (0);
}
