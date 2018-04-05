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
**make a double pointed list
**and allocated memory for the string
*/

t_dblist    *ft_dblist_make(char *string, int n)
{
    t_dblist *temp;

    temp = ft_dblist_new();
    temp->content = ft_strndup(string, n);
    return (temp);
}

/*
**makle new token and enques the list
*/

void        add_token(t_dblist *start, char *commands, int index_s, int index_e)
{
    t_dblist    *temp;

    temp = ft_dblist_make(&commands[index_s], index_e);
    ft_dblist_enque(start, temp);
}

/*
**Checks for escape char in current place, or the one before
*/

int         escape_char_check(char *commands, int index)
{
    if (commands[index] == ESCAPE)
        return (1);
    if ((index > 1) && commands[index - 1] == ESCAPE)
        return (1);
    return(0);
}

/*
**Checks if next char is number or redirect
**  if numbers, looks for redirect
**  if redirect, return
**Checks if current char is a redirect
**  if so, checks for presence of possible fork or number after
*/

int         redirect_check(char *commands, int index)
{
    int     count;

    count = 1;
    if (commands[index + 1] && ft_strchr(REDIR, commands[index + 1]))
        return (1);                                         // \/
    if (ft_isdigit(commands[index]))            //checking for 9>4
    {
        while (commands[index + count] && ft_isdigit(&commands[index + count]))
            count++;
        if (commands[index + count] && ft_strchr(REDIR, commands[index + count]))
        {
            while (commands[index + count] && ft_strchr(REDIR, commands[index + count]))
                count++;
            if (commands[index + count] && ft_isdigit(&commands[index + count])) 

        }
        else
            return (0);
        count = 1;
    }
    if (ft_isdigit(commands[index + 1]))        //checking for _9>4
    {
        while (commands[index + count] && ft_isdigit(commands[index + count]))
            count++;
        if (ft_strchr(REDIR, commands[index + count]))
            return (0);
        count = 0;
    }
    return (0);
}

/*
**checks for deliniators
**Will  return 0 if char is before delin
**OR return the # of char from that point until the next generic deliniator or looking for the one stated in arguments
*/

int         ft_isdelin(char *commands, int index)
{
    if (escape_char_check(commands, index))        //if escape char is present before delin
            return (0);
    if (ft_strchr(CMPLX_DELIN, commands[index]))    //if possible complex char present, find if it is.
    {
        if (redirect_check(commands, index))
            return(1);                           //check if redirect is solo, multiple, or with numbers before/after
    //    if (env_param_check(commands, index_s, index_e))                     //env param: if brackets present looks for end or bracket, if no braket looks for white space
    //        return (env_param_check(commands, index_s, index_e));
    //    if (logic_op_check(commands, index_s, index_e))                             //logical operators     looks for multiple & or |
    //        return (logic_op_check(commands, index_s, index_e));
    }
    if (ft_strchr(SIMPLE_DELIN, commands[index]))   //if deliniator is simple, the curent index is returned
        return (1);
    return (0);
}

t_dblist    *parse_start(char  *commands)
{
    t_dblist    *start;
    int         index_s;
    int         index_e;

    index_e = 0;
    start = ft_dblist_new();
    while (commands[index_s] != '\0')       //itteerating through the string
    {
        index_s = 0;
        while (commands[index_s + index_e] != '\0')     //itterating through current token
        {
            if (ft_isspace(commands[index_s + index_e]))        //checking for spaces
                break;
            if (ft_isdelin(commands, index_s + index_e))         //checking for if deliniator is present
                break;
            index_e++;
        }
        add_token(start, commands, index_s, index_e);          //make deliniator/word(operation) into a link, if quoted, goes into its own recursive break up.
        index_s += index_e;
    }
    //go through list and find quoted stuff
    return (start);
}