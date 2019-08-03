/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 22:23:18 by bomanyte          #+#    #+#             */
/*   Updated: 2019/04/23 22:25:55 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_lstsize(t_list *begin_lst)
{
	size_t i;

	i = 0;
	while (begin_lst)
	{
		begin_lst = begin_lst->next;
		i++;
	}
	return (i);
}
