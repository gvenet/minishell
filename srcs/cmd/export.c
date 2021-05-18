#include "minishell.h"

static char	**sort_array(char **arr)
{
	int		len;
	int		i;
	int		j;
	char	*temp;

	len = ft_strlen_2d(arr);
	i = -1;
	while (++i < len)
	{
		j = -1;
		while (++j < len)
		{
			if (ft_strncmp(arr[i], arr[j], ft_strlen(arr[i])) < 0)
			{
				temp = ft_strdup(arr[i]);
				del_fct(&arr[i]);
				arr[i] = ft_strdup(arr[j]);
				del_fct(&arr[j]);
				arr[j] = ft_strdup(temp);
				del_fct(&temp);
			}
		}
	}
	arr[len + 1] = NULL;
	return (arr);
}

static void	export_list(t_shell *sh)
{
	t_export	v;

	v.new_env = (char **)malloc(sizeof(char *) * (ft_strlen_2d(sh->env) + 2));
	v.i[0] = -1;
	while (sh->env[++v.i[0]])
		v.new_env[v.i[0]] = ft_strdup(sh->env[v.i[0]]);
	v.new_env[v.i[0]] = NULL;
	v.i[0] = -1;
	v.vars = sort_array(v.new_env);
	while (v.vars[++v.i[0]])
	{
		write(STDOUT_FILENO, "declare -x ", ft_strlen("declare -x "));
		v.split = ft_split(v.vars[v.i[0]], '=');
		write(STDOUT_FILENO, v.split[0], ft_strlen(v.split[0]));
		if (v.split[1])
		{
			write(STDOUT_FILENO, "=\"", ft_strlen("=\""));
			write(STDOUT_FILENO, v.split[1], ft_strlen(v.split[1]));
			write(STDOUT_FILENO, "\"", 1);
		}
		write(STDOUT_FILENO, "\n", 1);
		v.split = ft_strdel_2d(v.split);
	}
	v.vars = ft_strdel_2d(v.new_env);
}

void	ft_set_oldpwd(t_shell *sh, int cd_sucess)
{
	t_cmd_line	*oldpwd_cmd;
	char		*oldpwd;
	char		*pwd;

	oldpwd_cmd = (t_cmd_line *)msh_malloc(1, sizeof(t_cmd_line));
	init_cmd_line(&oldpwd_cmd);
	oldpwd = NULL;
	pwd = NULL;
	if (cd_sucess)
		f_getenv("PWD", sh, &pwd);
	oldpwd = ft_strjoin("OLDPWD=", pwd);
	if (!oldpwd)
		oldpwd = ft_strdup("OLDPWD");
	del_fct(&pwd);
	oldpwd_cmd->args = (char **)malloc(sizeof(char *) * 3);
	oldpwd_cmd->args[0] = ft_strdup("EXPORT");
	oldpwd_cmd->args[1] = ft_strdup(oldpwd);
	oldpwd_cmd->args[2] = NULL;
	export_algo(sh, oldpwd_cmd);
	oldpwd_cmd->args = ft_strdel_2d(oldpwd_cmd->args);
	free(oldpwd_cmd);
	oldpwd_cmd = NULL;
	del_fct(&oldpwd);
}

void	ft_set_pwd(t_shell *sh, char *newpwd)
{
	t_cmd_line	*newpwd_cmd;
	char		*pwd;
	char		*newpwd_to_free;

	newpwd_to_free = newpwd;
	newpwd_cmd = (t_cmd_line *)msh_malloc(1, sizeof(t_cmd_line));
	init_cmd_line(&newpwd_cmd);
	pwd = NULL;
	if (!newpwd)
		newpwd = ft_strdup("PWD");
	else
		newpwd = ft_strjoin("PWD=", newpwd_to_free);
	del_fct(&pwd);
	newpwd_cmd->args = (char **)malloc(sizeof(char *) * 3);
	newpwd_cmd->args[0] = ft_strdup("EXPORT");
	newpwd_cmd->args[1] = ft_strdup(newpwd);
	newpwd_cmd->args[2] = NULL;
	export_algo(sh, newpwd_cmd);
	newpwd_cmd->args = ft_strdel_2d(newpwd_cmd->args);
	free(newpwd_cmd);
	newpwd_cmd = NULL;
	del_fct(&newpwd_to_free);
	del_fct(&newpwd);
}

int	ft_export(t_shell *sh, void *cmd)
{
	int	ret;

	ret = 0;
	if ((((t_cmd_line *)cmd)->args[1]) == NULL)
		export_list(sh);
	else
		ret = export_algo(sh, cmd);
	return (ret_exit(sh, ret, E_SUCCESS));
}
