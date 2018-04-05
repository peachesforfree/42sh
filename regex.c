#include "libraries\libft\libft.h"

#define WORDS           'w'
#define NOT_Word        'W'
#define DIGITS          'd'
#define NOT_DIGIT       'D'
#define WHITE_SPACE     's'
#define NOT_WHITE       'S'
#define NOT             '^'
#define MATCH_ZERO      '*'
#define MATCH_MULT      '+'
#define MATCH_NUM       '#'
#define ANY_CHAR        '.'
#define MATCH_START     '>'
#define MATCH_END       '<'
#define ESCAPE          '\\'

typedef struct  s_regex
{
    int         i;
    int         k;

    int         matches_needed;
    int         match_start;
    int         match_end;
//    int         start_front;
//    int         start_rear;
    char        *start;
    char        *match_point
    char        *flags;
    char        *str;

}               t_regex;

void    construct_reg(t_reg *reg, char *str, char *flags)
{
    reg->i = 0;
    reg->k = 0;
    reg->matches_needed = 1;
    reg->match_at_most = 0;
    reg->match_start = 0;
    reg->match_end = 0;
//  reg->start_front = 0;
//  reg->start_end = 0;
    reg->start = NULL;
    reg->match_point = NULL;
    reg->str = str;
    reg->flags = flags;
}

int     assess_flag(t_reg *reg, int k)
{
    int     not_flg;
    int     num_match;

    not_flg = get_not_flg(reg->flags, &k)
    num_match = get_num(reg->flags, &k)
    if (reg->flags[reg->i] == WORDS)

    if (reg->flags[reg->i] == DIGITS)
    if (reg->flags[reg->i] == WHITE_SPACE)

    return (k);
}

int     flag_check(t_reg *reg)
{
    int k;

    k = 0;
    while (reg->str[reg->i + k] != '0')
    {
        if (reg->flags[k] == '\0')          //flag string done, match found
            return (1);
        if (reg->flags[k] == ESCAPE)
            k = assess_type(reg, ++k);
        else if (reg->flags[k] != ESCAPE && (reg->str[reg->i + k] == reg->flags[k]))
            k = asses_flags(reg, ++k);
        if (k == -1)
            return (0);
    }
    return (0);
}

char    *ft_regex(char *str, char *flags)
{
    t_regex     reg;

    if (!str || !flags)
        return (NULL);
    construct_reg(&reg, str, flags);
    while (str[reg.i])
    {
        reg.start = str[reg.i];
        if (flag_check(reg))
            return(results(reg));
        reg.i++;
    }
    return (NULL);
}


int main(int argc, char **argv)
{
    int x;
    int y;

    y = 1;
    while (y < argc)
    {
        ft_regex(&argv[y])
        y++;
    }
    return (0);
}