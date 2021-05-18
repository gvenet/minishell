#include "minishell.h"

void	reset_input_mode (void)
{
	tcsetattr (STDIN_FILENO, TCSANOW, &g_saved_attributes);
}

	/* Make sure stdin is a terminal. */
	/* Save the terminal attributes so we can restore them later. */
	/* Set the funny terminal modes. */
	/* Clear ICANON and ECHO. */
static void	set_input_mode (t_term *t)
{
	t->slot = ttyslot();
	if (!isatty (t->slot))
	{
		write (STDERR_FILENO, "Not a terminal.\n", \
		ft_strlen("Not a terminal.\n"));
		exit (EXIT_FAILURE);
	}
	tcgetattr (STDIN_FILENO, &g_saved_attributes);
	atexit (reset_input_mode);
	tcgetattr (STDIN_FILENO, &t->tattr);
	t->tattr.c_lflag &= ~(ICANON | ECHO);
	t->tattr.c_cc[VMIN] = 1;
	t->tattr.c_cc[VTIME] = 0;
	tcsetattr (STDIN_FILENO, TCSAFLUSH, &t->tattr);
}

void	init_termcap_msh(t_term *t)
{
	set_input_mode(t);
	t->name = ttyname(t->slot);
	t->term_type = getenv("TERM");
	if (t->term_type == NULL)
	{
		write(STDERR_FILENO, "TERM must be set (see 'env').\n", \
		ft_strlen("TERM must be set (see 'env').\n"));
		exit(-1);
	}
	t->ret = tgetent(NULL, t->term_type);
	if (t->ret == -1)
	{
		write(STDERR_FILENO, "Could not access to the termcap database..\n", \
		ft_strlen("Could not access to the termcap database..\n"));
		exit(-1);
	}
	else if (t->ret == 0)
	{
		write(STDERR_FILENO, "Terminal type ", ft_strlen("Terminal type "));
		write(STDERR_FILENO, t->term_type, ft_strlen(t->term_type));
		write(STDERR_FILENO, " is not defined in termcap database (or have too few \
		informations).\n", ft_strlen(" is not defined in termcap database (or have too \
		few informations).\n"));
		exit(-1);
	}
}
