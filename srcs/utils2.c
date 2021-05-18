#include "minishell.h"

void	*msh_malloc(size_t n, size_t size)
{
	void	*ptr;

	ptr = (void *)malloc(n * size);
	if (!ptr)
		exit_malloc_fail();
	ptr = ft_memset(ptr, 0, n);
	return (ptr);
}

int	ret_exit(t_shell *sh, int exit_code, int ret)
{
	sh->exit = exit_code;
	return (ret);
}

long long int	ft_atoi_msh(const char *nptr, long long int *nb)
{
	unsigned long int	val;
	int					signe;

	signe = 1;
	val = 0;
	while (*nptr == ' ' || *nptr == '\t' || *nptr == '\f' || *nptr == '\n' \
		 || *nptr == '\r' || *nptr == '\v')
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			signe = -signe;
		nptr++;
	}
	while ('0' <= *nptr && *nptr <= '9')
		val = 10 * val + (*nptr++ - '0');
	*nb = signe * val;
	if (val <= 9223372036854775807)
		return (E_SUCCESS);
	*nb = 255;
	return (E_FAIL);
}

char	*realloc_maison(char *ptr, int size)
{
	char	*nptr;
	int		i;

	nptr = (char *)ft_memalloc(size);
	if (!nptr)
	{
		gnl_free(&ptr);
		return (NULL);
	}
	i = 0;
	while (size-- > 1 && ptr[i])
	{
		nptr[i] = ptr[i];
		i++;
	}
	nptr[i] = '\0';
	gnl_free(&ptr);
	return (nptr);
}
