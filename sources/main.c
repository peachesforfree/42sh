
#include "../includes/shell.h"

t_dblist     *init_shell(char **environ)
{
    int     i;
    t_dblist  *start;
    t_dblist  *temp;

    i = 0;
    start = double_list_new();
    temp = start;
    while (environ[i] != NULL)
    {
        temp->content = (void*)ft_strdup(environ[i]);
        temp = double_insert_after(temp);
        i++;
    }
    return (start);
}

int     main(int argc, char **argv, char **environ)
{
    t_dblist  *env;
//    char    *line;
    int     cont;
    printf("%s\n", argv[0]);

    cont = argc;
    env = init_shell(environ);
    (env != NULL) ? (cont = 0) : (cont = 1);
    while (env->content != NULL)
    {
        printf("%s\n", env->content);
        env = env->next;
    }
/*    open(STDIN);
    while (cont)
    {
        putstr("$>");
        get_next_line(fd, line);
        parse_command();
        cont = execute();
    }
    shutdown_shell();*/    
    return (0);
}