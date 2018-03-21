
#ifndef DOUBLE_LINKED_LIST_H
# define    DOUBLE_LINKED_LIST_H
# include "../includes/shell.h"

typedef struct  s_dblist
{
    struct s_dblist    *next;
    struct s_dblist    *last;
    void        *content;
}               t_dblist;

t_dblist      *double_list_new(void);
t_dblist      *double_insert_after(t_dblist *current);

#endif
