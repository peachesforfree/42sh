#include "../../includes/lexing/lexing.h"

//divide up along < > | ; - >> << ` " ( ) $ &

t_dblist    *lexer_start(char  *commands)
{
    t_dblist    *start;
    int         i;

    if (command == NULL || ft_fronttrim(string) == '\0')
        return (NULL);
    while (commands[i] != '\0')
    {
        i = 0;
        while (ft_isspace(string[i]))
            i++;
        if (ft_strchr(string[i], DELIMITER) || number before redirect)
            i = (g_lookup[string[i])(&start, i, string)
        start = enqueue new dbl linked list
    }
    return (NULL);
}

void        g_lookup[9] = {
    [';'] = semicolin,
    ['>'] = pipeout,
    ['<'] = pipein,
    ['`'] = backtick,
    ['\"'] = dblquote,
    ['$'] = param,
    ['-'] = flags,
    ['('] = paren,
    [')'] = paren
}


t_token     g_builtin[8] = {
    {"cd", 2, CMDBUILTIN, 0, 0},
    {"echo", 4, CMDBUILTIN, "-n", 0},
    {"exit", 4, CMDBUILTIN, 0, 0},
    {"setenv", 6, CMDBUILTIN, 0, 0},
    {"unsetenv", 8, CMDBUILTIN, 0, 0},
    {"env", 3, CMDBUILTIN, 0, 0},
    {REDIR_R, 1, }
    {0, 0, 0, 0, 0}
};