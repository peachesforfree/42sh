#include "libft.h"


void        ft_dblist_bridge(t_dblist *first, t_dblist *second)
{
    if (!first || !second)
        return ;
    first->next = second;
    second ->last = first;
}