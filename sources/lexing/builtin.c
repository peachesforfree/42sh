#include "../../includes/lexing.h"

/*
**NAME, LEN, TOKEN TYPE, FLAGS, FLAGLEN 
**
*/
t_token     g_builtin[8] = {
    {"cd", 2, CMDBUILTIN, 0, 0},
    {"echo", 4, CMDBUILTIN, "-n", 0},
    {"exit", 4, CMDBUILTIN, 0, 0},
    {"setenv", 6, CMDBUILTIN, 0, 0},
    {"unsetenv", 8, CMDBUILTIN, 0, 0},
    {"env", 3, CMDBUILTIN, 0, 0},
    {0, 0, 0, 0, 0}
};