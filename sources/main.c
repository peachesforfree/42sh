
#include "../includes/shell.h"
/*
**Initializes the shell
**Copies over the environment variables to a 
**double linked list
*/


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

/*
**Lexes, parses, builds Abstract Syntax Tree, executes
*/

void    lex_parse_execute(char *command)
{
    
    lexer_start();
//    parser_start();
//    execute_start();
}

/*
**commented out is the parsing/dispatch that needs to be implemented
**Sergio without the hat will work on it March 21 and start
**anyone else can work on the termcaps stuff!!!
*/


int     main(int argc, char **argv, char **environ)
{
    t_dblist  *env;
    char    *line;
    int     cont;
    printf("%s\n", argv[0]);

    cont = argc;
    env = init_shell(environ);
    (env != NULL) ? (cont = 0) : (cont = 1);
    while (cont)
    {
        putstr("$>");
        get_next_line(STDIN_FILENO, line);
        lex_parse_execute(line);        
    }
    shutdown_shell();
    return (0);
}