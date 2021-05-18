#include "libft.h"

int	ft_putchar(int c)
{
	write(STDIN_FILENO, &c, 1);
	return (0);
}
