/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 10:58:38 by tyang             #+#    #+#             */
/*   Updated: 2018/03/26 13:49:20 by tyang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*	
**	note must compile with -ltermcap flag
**
**	for term caps, make sure to follow links listed in  termcaps.c
**
**	distinct statges of development
**	window formatting
**	reading in expected input "all keys"
**	reading control character ctrl+x ctrl+z and format properly ^C ^Z 
**	reading arrows and other misc buttons and handle properly within 
**	termcaps controls  
**	be able to account for open and closed ( ) " " ' ' and know when there 
**	is an incomplete number in order
**	If " " are open, continue asking user for more input
**
**	No other assesment of string is to be made in start_termcaps
**	return char * from start_termcaps();
**
**	best to follow guide at https://www.gnu.org/software/termutils/
**	manual/termcap-1.3/html_mono/termcap.html#TOC5
**	left off at https://www.gnu.org/software/termutils/manual/
**	termcap-1.3/html_mono/termcap.html in tutorial
*/

#include "../includes/termcaps.h"

/*
**  here termcaps is getting data about the current terminal
*/

void    init_terminal_data (void)
{
	char	*termtype;
	int		success;
	char	term_buffer[2048];

	bzero(term_buffer, 2048);
	termtype = getenv("TERM");
	printf("\n%s\t is your getenc(\"TERM\")\n", termtype);
	if (termtype == 0)
	{
		printf("Specify a terminal type with `setenv TERM <yourtype>'.\n");
		exit(1);
	}
	success = tgetent(term_buffer, termtype);
	printf("\n%d\t success from tgetent(term_buffer, termtype)\n", success);
	if (success < 0)
	{
		printf("Could not access the termcap data base.\n");
		exit(1);
	}
	if (success == 0)
	{
		printf("Terminal type `%s' is not defined.\n", termtype);
		exit(1);
	}
}

/*
**	here is where the program performs a function based on the keyinput 
**	every item here will need to be mapped messages dont need to be 
**	displayed for all of them.
*/

void	sighandler(int signum)
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

/*
**	This will be the loop where user input is put in, 
**	all key strokes nad strange key press combinations will need to be 
**	mapped to defines in termcap.h
**	signal() function is almost always running in the background 
**	receiveing keyboard input waiting to act on it i.e.
**	Kill program control+c or ^C or SIGINT
*/

int		start_termcaps(void)
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
