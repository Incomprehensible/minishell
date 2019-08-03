/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 21:47:48 by bomanyte          #+#    #+#             */
/*   Updated: 2019/04/23 15:00:30 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t				i;
	const unsigned char	*p;
	unsigned char		*q;

	i = 0;
	p = (unsigned char *)src;
	q = (unsigned char *)dst;
	if (q > p)
	{
		while (len > i++)
			q[len - i] = p[len - i];
		return (dst);
	}
	while (len-- > 0)
		*(q++) = *(p++);
	return (dst);
}
