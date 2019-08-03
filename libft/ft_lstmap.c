/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 21:39:08 by bomanyte          #+#    #+#             */
/*   Updated: 2019/04/23 15:06:27 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *new_lst;
	t_list *head;
	t_list *tmp;

	if (!lst || !f)
		return (NULL);
	tmp = f(lst);
	lst = lst->next;
	if (!(new_lst = ft_lstnew(tmp->content, tmp->content_size)))
		return (0);
	head = new_lst;
	while (lst)
	{
		tmp = f(lst);
		if (!(new_lst->next = ft_lstnew(tmp->content, tmp->content_size)))
		{
			free(new_lst);
			return (0);
		}
		lst = lst->next;
		new_lst = new_lst->next;
	}
	return (head);
}
