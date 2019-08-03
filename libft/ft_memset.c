/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 21:11:20 by bomanyte          #+#    #+#             */
/*   Updated: 2019/04/21 20:06:08 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;
	size_t			i;
	unsigned char	c1;

	i = 0;
	ptr = (unsigned char *)b;
	c1 = (unsigned char)c;
	while (i < len)
	{
		ptr[i] = c1;
		i++;
	}
	return (b);
}
