/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 19:59:06 by bomanyte          #+#    #+#             */
/*   Updated: 2019/04/23 15:13:16 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list **alst, void (*del)(void *, size_t))
{
	t_list *head;

	head = *alst;
	if (!(alst) || !(del))
		return ;
	*alst = (*alst)->next;
	del(head->content, head->content_size);
	free(head);
	head = NULL;
}
