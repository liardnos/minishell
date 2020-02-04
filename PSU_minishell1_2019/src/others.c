/*
** EPITECH PROJECT, 2019
** others
** File description:
** hello
*/

#include <unistd.h>
#include <stdlib.h>
#include "my.h"

char **my_str_to_word_array(char const *str, char split)
{
    int word_nb = 1;
    char *str2 = my_strdup(str);
    for (int i = 0; str2[i]; i++) str2[i] == split ? word_nb++ : 0;
    char **words = malloc(sizeof(char *) * (word_nb + 1));
    words[word_nb] = 0;
    words[0] = str2;
    int y = 1;
    for (int i = 0; str2[i]; i++){
        if (str2[i] == split){
            str2[i] = 0;
            words[y] = &str2[i+1];
            y++;
        }
    }
    return (words);
}

char *getpwd(void)
{
    int size = 1024;
    char *pwd;
    while (1){
        pwd = malloc(size);
        if (getcwd(pwd, size)) break;
        free(pwd);
        size += size;
    }
    pwd[my_strlen(pwd)+1] = 0;
    pwd[my_strlen(pwd)] = '/';
    return (pwd);
}

int find_reg3(char const *str, char const *reg_ex, int str_p, int reg_p)
{
    int total = 0;
    int i;
    if (reg_ex[reg_p] == '*'){
        for (i = 0; str[i+str_p] != '\0';i++)
            total += find_reg3(str, reg_ex, str_p+i, reg_p+1);
        total += find_reg3(str, reg_ex, str_p+i, reg_p+1);
    } else {
        while (reg_ex[reg_p] == str[str_p]){
            if (reg_ex[reg_p] == '\0' && str[str_p] == '\0') return (1);
            reg_p++, str_p++;
        }
        if (reg_ex[reg_p] == '*')
            total += find_reg3(str, reg_ex, str_p, reg_p);
    }
    return (total);
}
