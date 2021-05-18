#include "minishell.h"

void	ft_bs(int sign)
{
	sign += '0';
	write(STDERR_FILENO, "Quit: ", ft_strlen("Quit: "));
	write(STDERR_FILENO, &sign, sizeof(sign));
	write(2, "\n", 1);
}

void	ft_c(int sign)
{
	write(STDERR_FILENO, "\n", 1);
	(void)sign;
}
