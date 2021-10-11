/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junghan <junghan@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 11:08:50 by junghan           #+#    #+#             */
/*   Updated: 2021/10/11 11:08:57 by junghan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*tmp;
	t_list	*new;

	if (lst == 0 || f == 0)
		return (0);
	tmp = lst;
	new_lst = ft_lstnew(f(tmp->content));
	if (!new_lst)
		return (0);
	tmp = tmp->next;
	while (tmp)
	{
		new = ft_lstnew(f(lst->content));
		if (!new)
		{
			ft_lstclear(&new_lst, del);
			return (0);
		}
		ft_lstadd_back(&new_lst, new);
		tmp = tmp->next;
	}
	return (new_lst);
}
