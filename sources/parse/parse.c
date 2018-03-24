#include "../../includes/lexing/parse.h"

int         ffw_spaces(char *string)
{
    int i;

    i = 0;
    while (ft_isspace(string[i]))
        i++;
    return (i);
}

char        *ft_strndup(char *src, int n)
{
    char    *dest;
    int     i;
    
    i = 0;
    dest = ft_memalloc(n + 1);
    ft_memcpy(dest, src, n);
    return (dest);
}

t_dblist    *ft_dblist_enque(t_dblist *start, t_dblist *new)
{
    while (start->next != NULL)
        start = start->next;
    start->next = new;
    new->last = start;
}        

//divide up along < > | ; - >> << ` " ( ) $ &
/*
**This parses the single char tokens that are delimiters
*/
int         make_token(t_dblist *start, int i, char *commands)
{
    t_dblist    *tmp;

    tmp = ft_dblistnew();
    tmp->content = ft_strndup(commands[i]);
    ft_dblist_enque(start,tmp);
    return (1);
}

int         word_token(t_dblist *start, char *commands, int i)
{
    int         index;
    t_dblist    *temp;
    
    index = 0;
    while(commands[i + index] != '\0' && !ft_isspace(commands[index + i]))
        index++;
    temp = ft_dblistnew();
    temp->content = ft_strndup(commands[i], index)
    ft_dblist_enque(start, temp);
    return(index)
}

t_dblist    *parse_start(char  *commands)
{
    t_dblist    *start;
    int         i;

    start = ft_dblist_new();
    start->content = ft_strdup("empty");
    if (commands == NULL || commands[ffw_spaces(commands)] == '\0')
        return (NULL);
    while (commands[i] != '\0')
    {
        i +=ffw_spaces(commands[i]);
        if (ft_strchr(commands[i], DELIMITER))
            i += (g_parse_lookup[commands[i]])(&start, i, commands);
        else if (!ft_strchr(commands[i], DELIMITER))
            i += word_token(start, commands, i);
        //else if (search for number before/after carrots ?)
        else // commands[i] != NULL
            i++; // <-- what do ?
    }
    //remove first item in list and shift start to real first item in list
    return (start);
}

int        (*g_parse_lookup[127]) (t_dblist *start, int i, char *commands) =
{
    [';'] = make_token,
    ['|'] = make_token,
    ['>'] = pipeout,
    ['<'] = pipein,
    ['`'] = backtick,
    ['"'] = dblquote,
    ['$'] = param,
    ['-'] = make_token,
    ['&'] = make_token,
    ['('] = make_token,
    [')'] = make_token
}