#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <term.h>
#include <fcntl.h>
#include <strings.h>


void    init_terminal_data ()
{
  char *termtype = getenv ("TERM");
  int success;
  char  term_buffer[2048];

  bzero(term_buffer, 2048);
  printf("\n%s\t is your getenc(\"TERM\")\n", termtype);

  if (termtype == 0)
  {
    printf ("Specify a terminal type with `setenv TERM <yourtype>'.\n");
    exit(1);
  }

  success = tgetent (term_buffer, termtype);
  printf("\n%d\t success from tgetent(term_buffer, termtype)\n", success);
  if (success < 0)
  {
        printf ("Could not access the termcap data base.\n");
        exit(1);
  }
  if (success == 0)
  {
        printf("Terminal type `%s' is not defined.\n", termtype);
        exit(1);
  }
}

void sighandler(int);

int main () 
{
    printf("\nstarting init_terminal_data()\n");
    init_terminal_data();
    printf("\nsuccess getting ENV\n");

   signal(SIGINT, sighandler);
   while(1)
   {
      printf("Going to sleep for 1 second...\n");
      sleep(1); 
   }
   return(0);
}

void sighandler(int signum)
{
    printf("Caught signal %d\n", signum);
    if (signum == SIGINT)
    {
        printf("SIGINT %d killing proccess\n", signum);
        exit(1);
    }
    if (SIGTSTP == signum)
    {
        printf("SIGSTP %d suspending process\n", signum);
        pause();
    }
}
