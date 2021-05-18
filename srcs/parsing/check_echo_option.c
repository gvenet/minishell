#include <minishell.h>

static void	del_current_lst(t_shell *sh, t_list **l, t_list **p, t_list **q)
{
	sh->tmp_option_echo = E_TRUE;
	if (*p == *l)
	{
		*l = (*p)->next;
		free((*p)->content);
		free(*p);
		*p = *l;
	}
	else
	{
		(*q)->next = (*p)->next;
		free((*p)->content);
		free(*p);
		(*p) = (*q)->next;
	}
}

static int	is_option_n(char *s)
{
	if (*s++ == '-')
		while (*s == 'n')
			if (*++s == 0)
				return (1);
	return (0);
}

static int	is_echo(char **s, t_list *l)
{
	*s = l->content;
	*s = ft_str_tolower(l->content);
	if (!ft_strncmp(*s, "echo", ft_strlen(*s)))
		return (1);
	return (0);
}

static void	next_content(t_list **p, t_list **q)
{
	*q = *p;
	*p = (*p)->next;
}

t_list	*check_echo_option(t_shell *sh, t_list *l)
{
	t_list	*p;
	t_list	*q;
	char	*s;
	int		no_option;

	p = l;
	no_option = -1;
	if (is_echo(&s, l))
	{
		p = l;
		q = l;
		while (p)
		{
			s = p->content;
			if (is_option_n(s) && no_option <= 0)
				del_current_lst(sh, &l, &p, &q);
			else
			{
				no_option++;
				next_content(&p, &q);
			}
		}
		p = l;
	}
	return (p);
}
