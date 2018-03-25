
#include "../includes/shell.h"

void    TEST_print_list(t_dblist *commands)
{
    while (commands)
    {
        printf("%s\n", commands->content);
        if (commands->next != NULL)
            commands = commands->next;
        else
            exit(1);
    }
}
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
    start = ft_dblist_new();
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

void    lex_parse_execute(char *command, t_dblist *env)
{
    t_dblist    *commands;
    (void)env;
//    t_btree     *worktree;

    commands = parse_start(command);
//    worktree = parser_start(commands);
//    execute_start(commands, env);
    TEST_print_list(commands);
}

/*
**commented out is the parsing/dispatch that needs to be implemented
**Sergio without the hat will work on it March 21 and start
**anyone else can work on the termcaps stuff!!!
*/


int     main(int argc, char **argv, char **environ)
{
    t_dblist  *env;
//    char    buffer[4096];
    int     cont;
//    (void)argv;

    cont = argc;
    env = init_shell(environ);
    (env != NULL) ? (cont = 1) : (cont = 0);
    while (cont)
    {
//        write(1, "$>", 2);
//        ft_bzero(buffer, 4096);
//        read(STDIN_FILENO, buffer, 4095);
        lex_parse_execute(argv[1], env);        
    }
    //shutdown_shell();
    return (0);
}