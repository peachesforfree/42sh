#include "libft.h"

t_dblist      *ft_dblist_new()
{
    t_dblist *temp;

    if (!(temp = (t_dblist*)malloc(sizeof(t_dblist))))
        return (NULL);
    temp->next = NULL;
    temp->last = NULL;
    temp->content = NULL;
    return ((t_dblist*)temp);
}