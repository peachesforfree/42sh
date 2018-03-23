#include "libft.h"

char        *ft_frontstrim(char *string)
{
    int     i;
    
    i = 0;
    while (ft_isspace(string[i]) && str[i] != '\0')
        i++;
    return(string[i]);
}