

#ifndef PARSE_H
# define PARSE_H

# include "../shell.h"
# define DELIMITER      ";|><&`\"'$-()"
# define SIMPLE_DELIN   ";|\"`'()\\"
# define CMPLX_DELIN    "$><\\"
# define QUOTATIONS     "\"'`("
# define SPECIALS       "*?[]#~=%%"
# define PIPE           "|"
# define SEMICOLN       ";"
# define QUOTE          "\""
# define SNGQUOTE       "'"
# define BKTCK          "`"
# define FORK           "&"
# define REDIR          "<>"
# define REDIR_R        '>'
# define REDIR_RR       ">>"
# define REDIR_L        '<'
# define ESCAPE         '\\'
# define REDIR_LL       "<<"

t_dblist    *parse_start(char  *commands);

#endif