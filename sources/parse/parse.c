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
    if (i && commands)
        tmp->content = ft_strndup(commands, i);
    else
        tmp->content = NULL;
    if (start)
        ft_dblist_enque(start,tmp);
    else
    {
        tmp->next = NULL;
        tmp->last = NULL;
    }
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

/*need to write delimiter_present   && break_up_item
    for if a word in the linked list has a delimiter 
    the two will be broken up into 3 nodes, one for each word, and one for delimiter
    IF delimiter is at end/front, the one is broken into two nodes
    I.E.    file; stuff>file.txt 
*/

/*need to make quotations_present && inset_list_into_list
    outside of making the beginning and ending quotes into nodes
    the stuff within its goes back through parse_start and with that returned list
    it is inserted between the quotations.
    I.E.
    `echo "hello world"`
    `
    echo
    "hello world"
    `
            and will go through automatically again and become 

    `
    echo
    "
    hello world
    "
    `
    
    NOTE TO SELF: as is, in design, the lists will keep expanding for every pair of quotations
*/

t_dblist        *quotations_split(t_dblist *current, char *quote)
{
    t_dblist    *first;
    t_dblist    *second;
    char        *string;

    if (!current || !current->content)
        return (current);
    string = current->content;
    
    first = ft_dblist_new();
    first->content = ft_strdup(quote);
    ft_dblist_bridge(current->last, first);
    ft_dblist_bridge(first, current);

    //ft_dblist_bridge(current, temp);
    current->content = &string[1];
    string = current->content;
    string[ft_strlen(string) - 1] = '\0';

    second = ft_dblist_new();
    second->content = ft_strdup(quote);
    ft_dblist_bridge(second, current->next);
    ft_dblist_bridge(current, second);
    return (current);
}

void        break_out_op(t_dblist *start)
{
    t_dblist    *current;
    int         index;
    char        *current_string;

    current = start;
    while (current)
    {
        index = 0;
        current_string = current->content;
        while (current_string[index] != '\0')
        {
            if ((ft_strlen(current_string) > 1) && (ft_strchr(QUOTATIONS, (int)current_string[index])))    //maybe make a check for an escape? or a corresponding end
                current = quotations_split(current, QUOTE);    //will check for quoations and split into extra lists
            //if (single quote)
            //if (redirection)
            if (current == NULL)
                break ;
            index++;
        }
        current = current->next;
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
        if (ft_strchr(QUOTATIONS, commands[i]))
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
    break_out_op(start);             // <--- make this return the newly expanded list which is inserted into the tree... leading to recursive calls to continue doing the same
    return (start);
}