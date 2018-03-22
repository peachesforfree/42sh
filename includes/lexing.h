

#ifndef LEXING_H
# define LEXING_H

# include "shell.h"
# define DELINEATOR ";|><&` "
# define PIPE   "|"
# define END    ";"
# define QUOTE "\""
# define BKTCK "`"
# define REDIR_R ">"
# define REDIR_RR ">>"
# define REDIR_L "<"
# define REDIR_LL "<<"
# define CMDBUILTIN     0b00000001
# define CMDREGULAR     0b00000010
# define CMDDELIN       0b00000100
# define CMDOP          0b00001000

typedef struct  s_token
{
    char        *name;
    int         len;
    char        type;
    char        *flags;
    int         flglen;
}               t_token;

extern  t_token   g_builtin[8];

#endif