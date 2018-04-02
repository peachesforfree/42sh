#include "libft.h"

void            ft_dblist_free(t_dblist *list)
{
    if (list == NULL)
        return ;
    if (list->content != NULL)
        free(list->content);
    free(list);
}