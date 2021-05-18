#include "libft.h"

int	str_alnum(char *str)
{
	int	i;

	i = -1;
	if (!str)
		return (0);
	while (str[++i])
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
	return (1);
}
