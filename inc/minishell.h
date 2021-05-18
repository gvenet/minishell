/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 10:24:17 by smorel            #+#    #+#             */
/*   Updated: 2021/03/05 10:24:19 by smorel           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define	HISTSIZE 500
// echo $HISTSIZE = 500 in bash

# include "libft.h"
# include "get_next_line.h"
# include "normy_ez.h"
// # define _POSIX_SOURCE
# include <unistd.h>
// # undef _POSIX_SOURCE
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include <limits.h>
# include <term.h>
# include <curses.h>
# include <termios.h>
# include <signal.h>

struct termios	g_saved_attributes;

typedef struct s_term
{
	int				slot;
	char			*name;
	int				ret;
	char			*term_type;
	char			*ku;
	char			*kd;
	char			*kl;
	char			*kr;
	int				position;
	struct termios	tattr;
}	t_term;

typedef struct s_redirect
{
	int			id_o;
	int			fd_o;
	char		*name_o;
	int			id_i;
	int			fd_i;
	char		*name_i;
	int			id_n;
	int			fd_n;
	char		*name_n;
}	t_redir;

typedef struct s_cmd_line
{
	int			cmd;
	int			option_echo;
	int			redir_pipe;
	t_redir		*redir;
	char		**args;
}	t_cmd_line;

typedef struct s_history
{
	char	**history;
	int		history_len;
	int		current_history;
}	t_history;

typedef struct s_shell
{
	int			exit;
	char		**env;
	t_list		*cmd;
	t_list		*lst_arg;
	t_redir		*redir;
	int			redir_process_engaged;
	int			getenv_process_engaged;
	int			env_does_not_exist;
	int			tmp_option_echo;
	int			pars_char;
	int			redir_id;
	t_term		*t;
	t_history	hist;
	int			fd_sav[2];
}	t_shell;

typedef struct s_child_process
{
	int		i;
	int		y;
	int		fd;
	char	**path;
	char	**env_path;
}	t_c_pid;

typedef struct s_export_variables
{
	char	**new_env;
	char	**vars;
	char	**split;
	char	*var_to_set;
	int		i[2];
}	t_export;

typedef struct s_magic_pipe
{
	int	pid1;
	int	pid2;
	int	fd1[2];
	int	fd2[2];
	int	change_pipe;
	int	wstatus;
}	t_pipe;

enum	e_cmd
{
	E_NO_MATCH,
	E_ENV,
	E_CD,
	E_PWD,
	E_EXIT,
	E_EXPORT,
	E_UNSET,
	E_ECHO,
};

enum	e_bool
{
	E_FALSE,
	E_TRUE,
};

enum	e_ccmd
{
	CMD_ARG_1_MAX = 4,
};

enum	e_valeur
{
	E_FAIL = - 1,
	E_SUCCESS,
	E_READING,
};

enum	e_redir
{
	RAFTSUP = 1,
	DRAFTSUP,
	RAFTINF,
	DRAFTN,
	RAFTN,
	DRAFTNP,
	RAFTNP,
};

/*
**	---------- CMD PART ----------
*/

/*
**  CHECK_CMD
*/
int		test_cmd(t_shell *sh, t_cmd_line *cmd, int id, int err);

/*
**  CMD1
*/
int		ft_exit(t_shell *sh, void *b);
int		ft_unset(t_shell *sh, void *b);
void	ft_unset_algo(t_shell *sh, char *var_to_unset);

/*
**  CMD2
*/
int		ft_pwd(t_shell *sh, void *size);
int		ft_env(t_shell *sh, void *b);
int		ft_echo(t_shell *sh, void *cmd);
int		ft_cd(t_shell *sh, void *b);
int		ft_nomatch(t_shell *sh, void *b);

/*
**	EXEC
*/
int		exec_cmd(t_shell *sh);

/*
**	EXPORT
*/
int		ft_export(t_shell *sh, void *b);

/*
**	PIPES_UTILS
*/
void	magic_pipe_pid(t_shell *sh, t_cmd_line	*current_cmd, \
		int (*arr[8])(t_shell *sh, void *b), t_pipe p);
void	pipe_choice(t_pipe *p, t_cmd_line *current_cmd);
void	ft_close_pipe(int fd[2]);

/*
** PIPES
*/
void	magic_pipe(t_shell *sh, t_list **cmd_list, \
		int (*arr[8])(t_shell *sh, void *b));

/*
** REDIRECTIONS
*/
void	redirections(t_shell *sh, t_list **cmd_list, \
		int (*arr[8])(t_shell *sh, void *b));

/*
** UTILS
*/
char	*add_new_line(void);
char	*add_new_space(void);
int		f_getenv(char *var, t_shell *sh, char **value);
int		ft_strlen_2d(char **s);
int		check_export_name(char *s);
int		str_digit(char *str);
void	ft_bs(int sign);
void	ft_c(int sign);

/*
**	---------- ---------- ----------
*/

/*
**	---------- PARSING PART ----------
*/

/*
**	PARSING
*/
int		get_line(t_shell *sh);
int		pars_line(t_shell *sh, char *buf);
int		analysis_arg(t_shell *sh, char **buf);
int		exit_status_len(t_shell *sh, char **buf, int ret);
int		next_char_ana(t_shell *sh, char **buf, int ret);
char	*fill_arg(t_shell *sh, char **buf, char *arg, int n);
char	*treatment_arg(t_shell *sh, char **buf, char *s);
t_list	*check_echo_option(t_shell *sh, t_list *l);

/*
** REDIRECT
*/
int		is_redir(t_shell *sh, char **buf);
int		analysis_redir(t_shell *sh, char **buf, int redir_id);
char	*file_path(char *path);
int		file_creation_np(t_shell *sh, char *b_ptr, int n, int id);

/*
** ENV
*/

char	*treatment_tild(char **buf, char *s);
char	*treatment_sh_exit(t_shell *sh, char **buf, char *s);
char	*treatment_env(t_shell *sh, char **buf, char *s);
int		analysis_env(t_shell *sh, char **buf, int *ret);
int		analysis_tild(t_shell *sh, char **buf, int ret);
int		is_tild(char **buf, int ret);
int		is_env(char **buf);

/*
** CREATE / CLEAR LST
*/

void	create_cmd_list(t_shell *sh);
void	clear_lst_arg(t_list **lst);
void	clear_lst_cmd(t_list **lst);
void	clear_sh_redir(t_shell *sh);

/*
** PARSING UTILS
*/
int		is_sep(char c);
int		is_quot(char c);
void	display_lst_cmd_line(t_shell *sh);
char	*trim_ws(char *buf);
int		is_bckslash(char **buf);
int		check_unique_sep_error(char *buf);
int		check_sep_end_line(t_list *l, char **buf);
void	exec_for_pipe(t_shell *sh);

/*
** exit
*/
void	exit_malloc_fail(void);

/*
**	---------- ---------- ----------
*/

/*
**	---------- TERMCAP PART ----------
*/

/*
** FCT_TERMCAP
*/
void	del_termcap(char **term, t_shell *sh);
void	tab_termcap(char **term, t_shell *sh);

/*
** HISTORY
*/
int		cmd_history(t_shell *sh, int read, char **term);

/*
** PARS
*/
char	*termcap_pars(t_shell *sh);

/*
** TERMCAP
*/
void	reset_input_mode (void);
void	init_termcap_msh(t_term *t);

/*
**	---------- ---------- ----------
*/

/*
**	----------				----------
*/

/*
**	EXIT
*/
void	free_shell(t_shell *sh, unsigned int code_err);

/*
**	INIT
*/
void	init_cmd_line(t_cmd_line **cmd_line);
void	init_sh(int argc, char **argv, char **env, t_shell *sh);
void	init_redir(t_shell *sh);

/*
**	UTILS
*/
void	del_fct(char **x);
void	del_fct_int(int **x);
void	*msh_malloc(size_t n, size_t size);
int		ret_exit(t_shell *sh, int exit_code, int ret);
void	ms_prompt(void);
char	*realloc_maison(char *ptr, int size);

/*
**	---------- ---------- ----------
*/

/*
** TO SORT
*/
void	ft_set_oldpwd(t_shell *sh, int cd_sucess);
void	ft_set_pwd(t_shell *sh, char *newpwd);
int		export_algo(t_shell *sh, void *cmd);
int		ft_cd_val_null(t_shell *sh, char *val);
void	magic_pipe_loop(t_pipe *p, t_cmd_line **current_cmd, \
		t_list ***cmd_list);
void	fc_cc(int a);

#endif
