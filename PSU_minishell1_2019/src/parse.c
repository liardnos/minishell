/*
** EPITECH PROJECT, 2019
** parse
** File description:
** hello
*/

#include <unistd.h>
#include <stdlib.h>
#include "my.h"

char *get_var(char *str, lld_t *env)
{
    char *reg_ex = my_strcat(str, "=*");
    char *var = 0;

    for (int i = 0; i < (long int)env->data; i++){
        if (find_reg3(lld_read(env, i), reg_ex, 0, 0)){
            var = my_strdup(lld_read(env, i));
        }
    }
    free(reg_ex);
    if (var == 0) return (0);
    int x;
    for (x = 1; var[x-1] != '=' && var[x-1]; x++);
    for (int i = 0; var[x-1]; var[i] = var[x], x++, i++);
    return (var);
}

int setenv_parse(char *av1)
{
    char c = av1[0];
    if (c != '_' && !('A' <= c && 'Z' >= c) && !('a' <= c && 'z' >= c)){
        write(2, "setenv: Variable name must begin with a letter.\n", 48);
        return (1);
    }
    av1++;
    for (; *av1; av1++){
        c = *av1;
        if (c != '_' && !('A' <= c && 'Z' >= c) && !('a' <= c && 'z' >= c) &&
        c != '.' && !('0' <= c && '9' >= c)){
            write(2, "setenv: Variable name must contain ", 35);
            write(2, "alphanumeric characters.\n", 25);
            return (1);
        }
    }
    return (0);
}

void parsing_c(char *str, lld_t *av_lld)
{
    int cote = 0;
    int y = 0;
    for (int x = 0; str[x]; x++, y++){
        if (str[x] != '\\'){
            str[x] == '\'' && str[x-1] != '\\' && !(cote&2) ? cote ^= 1 : 0;
            str[x] == '"' && str[x-1] != '\\' ? cote ^= 2 : 0;
            str[y] = str[x];
            if (str[x] == ' ' && !cote && str[x-1] != '\\'){
                str[y] = 0;
                lld_insert(av_lld, (long int)av_lld->data, &str[y+1]);
            }
        } else
            str[y] = str[x+1], x++;
    }
    str[y] = 0;
}

char **parsing_b(char *str)
{
    lld_t *av_lld = lld_init();
    lld_insert(av_lld, (long int)av_lld->data, str);
    parsing_c(str, av_lld);
    char **words = malloc(sizeof(char *) * ((long int)av_lld->data + 1));
    words[(long int)av_lld->data] = 0;
    for (int i = 0; (long int)av_lld->data; words[i] = lld_pop(av_lld, 0), i++);
    lld_free(av_lld);
    char c;
    for (int i = 0; words[i] && words[i][0]; i++){
        if (words[i][0] == '\'' || words[i][0] == '\"') words[i]++;
        c = words[i][my_strlen(words[i])-1];
        if (c == '\'' || c == '\"') words[i][my_strlen(words[i])-1] = 0;
    }
    return (words);
}

char **parsing_a(char *line)
{
    char *str = my_strdup(line);
    int cote = 0;
    int x = 0;
    int y = 0;
    for (; str[x] == ' ' || str[x] == '\t'; x++);
    for (; str[x]; x++) {
        if (str[x+1] == '\t' && !cote && str[x] != '\\')
            str[x+1] = ' ';
        str[x] == '\'' && str[x-1] != '\\' && !(cote&2) ? cote ^= 1 : 0;
        str[x] == '"' && str[x-1] != '\\' ? cote ^= 2 : 0;
        if (cote || !(str[x] == ' ' && str[x+1] == ' ')){
            str[y] = str[x];
            y++;
        }
    }
    str[y] = 0;
    if (cote) return (0);
    return (parsing_b(str));
}
