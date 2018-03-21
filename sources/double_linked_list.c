#include "../includes/double_linked_list.h"

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

t_dblist      *double_insert_after(t_dblist *current)
{
    if (current == NULL)
        return (NULL);
    current->next = double_list_new();
    current->next->last = current;
    return (current->next);
}