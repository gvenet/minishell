/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorel <smorel@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 20:01:57 by smorel            #+#    #+#             */
/*   Updated: 2020/11/20 20:02:05 by smorel           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lst_f;
	t_list	*elem_f;

	if (!f || !del)
		return (NULL);
	lst_f = NULL;
	while (lst)
	{
		elem_f = ft_lstnew(f(lst->content));
		if (!elem_f)
		{
			ft_lstclear(&lst_f, del);
			return (NULL);
		}
		ft_lstadd_back(&lst_f, elem_f);
		lst = lst->next;
	}
	return (lst_f);
}
