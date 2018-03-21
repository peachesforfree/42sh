#include "42sh.h"

int     main(int argc, char **argv, char **environ)
{
    int     cont;
    char    **env;
    char    *line;
    char    **lines;

    cont = init_shell(argc, argc, env, environ);
    open(STDIN);
    while (cont)
    {
        putstr("$>");
        get_next_line(fd, line);
        parse_command();
        cont = execute();
    }
    shutdown_shell();    
    return (0);
}