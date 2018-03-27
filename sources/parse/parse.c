#include "../../includes/parse/parse.h"

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

int         ffw_spaces(char *string)
{
    int i;

    i = 0;
    while (ft_isspace(&string[i]))
        i++;
    return (i);
}

/*
**This parses the single char tokens that are delimiters
**< > | ; - >> << ` " ( ) $ &
*/

int         make_token(t_dblist *start, int i, char *commands)
{
    t_dblist    *tmp;

    tmp = ft_dblist_new();
    tmp->content = ft_strndup(commands, i);
    ft_dblist_enque(start,tmp);
    return (i);
}

/*
**This parses whole words into tokens
**delimited by white space
*/

int         word_token(t_dblist *start, int i, char *commands)
{
    int     index;
    
    index = 0;
    while(commands[i + index] != '\0' && !ft_isspace(&commands[index + i]))
        index++;
    make_token(start, index, &commands[i]);
    return(index);
}

char        find_end_marker(char start)
{
    char end;

    end = '\0';
    (start == '\"')?(end = '\"'):(0);
    (start == '`')?(end = '`'):(0);
    (start == '(')?(end = ')'):(0);
    (start == '[')?(end = ']'):(0);
    (start == '{')?(end = '}'):(0);
    (start == '\'')?(end = '\''):(0);
    return (end);
}

/*
**if quoted
**Token is made to the last corresponding quotation mark
*/

int         quoted(t_dblist *start,char *commands)
{
    int     index;
    char    marker;
    char    end_marker;

    marker = commands[0];
    end_marker = find_end_marker(marker);
    index = 1;
    while (commands[index] != '\0')
    {
        if (commands[index] == end_marker)
            break;
        index++;
    }
    make_token(start, index + 1, commands);
    return (index + 1);
}

t_dblist    *break_up_item(t_dblist *current)
{
    t_dblist    *temp;
    int         first_len;
    int         second_len;

    temp = ft_dblist_new();
    
    return (temp);
}

/*need to write delimiter_present   && break_up_item
    for if a word in the linked list has a delimiter 
    the two will be broken up into 3 nodes, one for each word, and one for delimiter
    IF delimiter is at end/front, the one is broken into two nodes
*/

/*need to make quotations_present && inset_list_into_list
    outside of making the beginning and ending quotes into nodes
    the stuff within its gors back through parse_start and with that returned list
    it is inserted between the quotations.

    NOTE TO SELF: as is, in design, the lists will keep expanding for every pair of quotations
*/
void        break_out_op(t_dblist *start)
{
    t_dblist    *temp;
    int         index;

    index = 0;
    temp = start;
    while (temp)
    {
        if (delimiter_present((char*)temp->content))
            temp = break_up_item(temp);
        else if (quotations_present(temp))
            temp = insert_list_into_list(temp);
        else if (temp->next == NULL)
            break;
        else
            temp = temp->next;
    }
}

//      ^^ start here !!!

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
        i += ffw_spaces(&commands[i]);
        if (ft_strchr(QUOTED_CHR, commands[i]))
        {
            i += quoted(start, &commands[i]);
            continue;
        }
        else if (!ft_isspace(&commands[i]))
        {
            i += word_token(start, i, commands);
            continue;
        }
    }
    break_out_op(start);
    return (start);
}