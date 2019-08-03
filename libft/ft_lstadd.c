/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 20:42:30 by bomanyte          #+#    #+#             */
/*   Updated: 2019/04/20 21:31:31 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd(t_list **alst, t_list *new)
{
	t_list *tmp;

	if (!(new))
		return ;
	if (*alst != 0)
	{
		if ((*alst)->next)
			tmp = (*alst)->next;
		if (!((*alst)->next))
			tmp = *alst;
		*alst = new;
		new->next = tmp;
	}
	else
		*alst = new;
}
