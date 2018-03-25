#include "../../includes/parse/parse.h"

int        (*g_parse_lookup[127]) (t_dblist *start, int i, char *commands) =
{
    [';'] = make_token,
    ['|'] = make_token,
    ['>'] = pipeout,
//    ['<'] = pipein,
//    ['`'] = backtick,
//    ['"'] = dblquote,
    ['$'] = param,
    ['-'] = make_token,
    ['&'] = make_token,
    ['('] = make_token,
    [')'] = make_token
};

//counts the number of digits before the redirections while still keeping after index of 0
int         prefix_num_len(char *commands, int i)
{
    int index;

    index = 0;
    while ((i + index) >= 1)
    {
        if (ft_isdigit(commands[i + index - 1]))
            index--;
        else
            break;
    }
    return (index);
}


/*
*           LAST TOOK OFF HERE 
*   trying to figure out how to handle numbers on redirections i.e. 3>1     >2      3>  3>&1 ?  2&>1 ?
*   last at the count for digits after the carrot and how to get that into its own db_list
*/

int         pipeout(t_dblist *start, int i, char *commands)
{
    int index;
    t_dblist *temp;

    index = 0;
    if (i > 0 && ft_isdigit(commands[i - 1]))
    {
        index += prefix_num_len(commands, i);
        tmp = ft_dblist_new();
        tmp->content = ft_strndup(&commands[i + index], (index * -1));
        ft_dblist_enque(start,tmp);
    }
    index = 0;
    tmp = ft_dblist_new();
    tmp->content = ft_strndup(&commands[i], 1);
    ft_dblist_enque(start,tmp);
    while (commands [i + index + 1] && ft_isdigit(commands[i + index + 1]))
        index++;
    if (index)
    return (index);
}

int         ffw_spaces(char *string)
{
    int i;

    i = 0;
    while (ft_isspace(&string[i]))
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
    return (start);
}    

/*
**This parses the single char tokens that are delimiters
**< > | ; - >> << ` " ( ) $ &
*/

int         make_token(t_dblist *start, int i, char *commands)
{
    t_dblist    *tmp;

    tmp = ft_dblist_new();
    tmp->content = ft_strndup(&commands[i], 1);
    ft_dblist_enque(start,tmp);
    return (1);
}

/*
**This parses whole words into tokens
**delimited by white space
*/

int         word_token(t_dblist *start, int i, char *commands)
{
    int         index;
    t_dblist    *temp;
    
    index = 0;
    while(commands[i + index] != '\0' && !ft_isspace(&commands[index + i]) && !ft_strchr(DELIMITER, commands[i + index]))
        index++;
    temp = ft_dblist_new();
    temp->content = ft_strndup(&commands[i], index);
    ft_dblist_enque(start, temp);
    return(index);
}

/*
**Deals with the parsing with ${ }
**
*/

int         param(t_dblist *start, int i, char *commands)
{
    int         index;
    t_dblist    *temp;
    
    index = 0;
    while (!ft_isspace(&commands[i + index]) && ft_strchr(DELIMITER, commands[i]))
        index++;
    temp = ft_dblist_new();
    temp->content = ft_strndup(&commands[i], index);
    ft_dblist_enque(start, temp);
    return (index);
}

t_dblist    *parse_start(char  *commands)
{
    t_dblist    *start;
    int         i;

    i = 0;
    start = ft_dblist_new();
    start->content = ft_strdup("empty");
    if (commands == NULL || commands[ffw_spaces(commands)] == '\0')
        return (NULL);
    while (commands[i] != '\0')
    {
        i +=ffw_spaces(&commands[i]);
        if (ft_strchr(DELIMITER, commands[i]))
            i += (*g_parse_lookup[(int)commands[i]])(start, i, commands);
        else if (!ft_strchr(DELIMITER, commands[i]))
            i += word_token(start, i, commands);
        //else if (search for number before/after carrots ?)
        else // commands[i] != NULL
            i++; // <-- what do ?
    }
    //remove first item in list and shift start to real first item in list
    return (start);
}
