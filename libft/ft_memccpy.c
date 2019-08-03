/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_ccpy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 20:42:26 by bomanyte          #+#    #+#             */
/*   Updated: 2019/04/21 20:04:18 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*p;
	unsigned char	*q;

	p = (unsigned char *)src;
	q = (unsigned char *)dst;
	while (n--)
	{
		*q = *p;
		if (*p == (unsigned char)c)
		{
			q++;
			return (q);
		}
		p++;
		q++;
	}
	q = 0;
	return ((void *)q);
}
