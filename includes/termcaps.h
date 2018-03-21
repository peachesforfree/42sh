
//read notes in termcaps.c
#ifndef TERMCAPS_H
# define    TERMCAPS_H

# include <signal.h>
# include <term.h>

int start_termcaps(void);
void sighandler(int);

#endif