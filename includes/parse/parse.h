

#ifndef PARSE_H
# define PARSE_H

# include "../shell.h"
# define DELIMITER      ";|><&`\"'$-()"
# define DELIM_WO_QUOTE ";|><&$-"
# define QUOTATIONS     "\"'`("
# define SPECIALS       "*?[]#~=%%"
# define PIPE           "|"
# define SEMICOLN       ";"
# define QUOTE          "\""
# define BKTCK          "`"
# define FORK           "&"
# define REDIR_R        ">"
# define REDIR_RR       ">>"
# define REDIR_L        "<"
# define REDIR_LL       "<<"
# define CMDBUILTIN     0b00000001
# define CMDREGULAR     0b00000010
# define CMDDELIN       0b00000100
# define CMDOP          0b00001000

t_dblist    *parse_start(char  *commands);
int         make_token(t_dblist *start, int i, char *commands);
int         pipeout(t_dblist *start, int i, char *commands);
//int         pipein(t_dblist *start, int i, char *commands);
//int         backtick(t_dblist *start, int i, char *commands);
//int         dblquote(t_dblist *start, int i, char *commands);
//int         param(t_dblist *start, int i, char *commands);

typedef struct  s_token
{
    char        *name;
    int         len;
    char        type;
    char        *flags;
    int         flglen;
}               t_token;

#endif