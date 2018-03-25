#include "libft.h"

t_dblist      *double_insert_after(t_dblist *current)
{
    if (current == NULL)
        return (NULL);
    current->next = ft_dblist_new();
    current->next->last = current;
    return (current->next);
}