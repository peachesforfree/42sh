#include "libft.h"

t_dblist      *double_list_new()
{
    t_dblist *temp;

    if (!(temp = (t_dblist*)malloc(sizeof(t_dblist))))
        return (NULL);
    temp->next = NULL;
    temp->last = NULL;
    temp->content = NULL;
    return (temp);
}