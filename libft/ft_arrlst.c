/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrlst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 20:47:34 by bomanyte          #+#    #+#             */
/*   Updated: 2019/04/23 19:04:07 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_arrlst(int num)
{
	t_list	*tmp;
	t_list	*begin;

	if (num-- > 0)
	{
		if (!(tmp = ft_lstnew(0, 0)))
			return (0);
		begin = tmp;
		while (num > 0)
		{
			if (!(tmp->next = ft_lstnew(0, 0)))
			{
				free(tmp);
				return (0);
			}
			tmp = tmp->next;
			num--;
		}
		return (begin);
	}
	else
		return (0);
}
