#include <minishell.h>

char	*treatment_tild(char **buf, char *s)
{
	char	*var_val;
	char	*var_val_ptr;
	int		i;

	i = 0;
	(*buf)++;
	var_val = getenv("HOME");
	i = ft_strlen(var_val);
	if (i > 0)
	{
		var_val_ptr = var_val;
		while (i--)
			*s++ = *var_val_ptr++;
	}
	return (s);
}

char	*treatment_sh_exit(t_shell *sh, char **buf, char *s)
{
	int		i;
	char	*d;
	char	*d_ptr;

	i = (int)ft_intlen(sh->exit);
	d = ft_itoa(sh->exit);
	d_ptr = d;
	while (i--)
		*s++ = *d_ptr++;
	free(d);
	(*buf) += 2;
	return (s);
}

static void	fill_str(char **s, char **var_val, char **var_val_ptr, int i)
{
	if (i > 0)
	{
		*var_val_ptr = *var_val;
		while (i--)
			*(*s)++ = *(*var_val_ptr)++;
		free (*var_val);
	}
}

char	*treatment_env(t_shell *sh, char **buf, char *s)
{
	char	*var;
	char	*var_ptr;
	char	*var_val;
	char	*var_val_ptr;
	int		i;	

	var = NULL;
	i = 0;
	(*buf)++;
	while ((*buf)[i] && ft_isalnum((*buf)[i]))
		i++;
	var = (char *)msh_malloc(i + 1, sizeof(char));
	var_ptr = var;
	while (i--)
		*var_ptr++ = *(*buf)++;
	i = f_getenv(var, sh, &var_val);
	fill_str(&s, &var_val, &var_val_ptr, i);
	free (var);
	return (s);
}

int	analysis_env(t_shell *sh, char **buf, int *arg_size)
{
	int		i;
	int		ret;
	char	*var;
	char	*var_ptr;

	ret = 0;
	(*buf)++;
	var = NULL;
	i = 0;
	while ((*buf)[i] && ft_isalnum((*buf)[i]))
		i++;
	var = (char *)msh_malloc(i + 1, sizeof(char));
	var_ptr = var;
	while (i--)
		*var_ptr++ = *(*buf)++;
	i = f_getenv(var, sh, NULL);
	if (i > 0)
		ret += i;
	else
		sh->env_does_not_exist = E_TRUE;
	free(var);
	*arg_size += ret;
	return (*arg_size);
}
