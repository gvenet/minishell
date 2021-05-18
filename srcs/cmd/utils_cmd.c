#include "minishell.h"

char	*add_new_space(void)
{
	char	*output;

	output = (char *)malloc(2);
	output[0] = ' ';
	output[1] = 0;
	return (output);
}

char	*add_new_line(void)
{
	char	*output;

	output = (char *)malloc(2);
	output[0] = '\n';
	output[1] = 0;
	return (output);
}

int	f_getenv(char *var, t_shell *sh, char **value)
{
	char	**env_split;
	char	*var_value;
	int		i;
	int		ret;

	i = -1;
	ret = -1;
	while (sh->env[++i])
	{
		env_split = ft_split(sh->env[i], '=');
		if (!ft_strncmp(env_split[0], var, 1 + ft_strlen(env_split[0])))
			ret = i;
		env_split = ft_strdel_2d(env_split);
	}
	if (ret == -1)
		return (E_FAIL);
	var_value = sh->env[ret];
	while (*var_value != '=' && *var_value)
		var_value++;
	if (!(var_value))
		return (0);
	ret = ft_strlen(++var_value);
	if (value)
		*value = ft_strdup(var_value);
	return (ret);
}

int	ft_strlen_2d(char **s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

int	check_export_name(char *s)
{
	char	**split;
	int		valid;

	valid = 1;
	split = ft_split(s, '=');
	if (!split[0])
	{
		write(STDERR_FILENO, "export: `", ft_strlen("export: `"));
		write(STDERR_FILENO, s, ft_strlen(s));
		write(STDERR_FILENO, "': not a valid identifier\n", \
		ft_strlen("': not a valid identifier\n"));
		valid = 0;
	}
	else if (ft_isdigit(*split[0]) || !str_alnum(split[0]))
	{
		write(STDERR_FILENO, "export: `", ft_strlen("export: `"));
		write(STDERR_FILENO, s, ft_strlen(s));
		write(STDERR_FILENO, "': not a valid identifier\n", \
		ft_strlen("': not a valid identifier\n"));
		valid = 0;
	}
	split = ft_strdel_2d(split);
	if (valid)
		return (E_SUCCESS);
	return (E_FAIL);
}
