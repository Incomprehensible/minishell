/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 21:51:14 by bomanyte          #+#    #+#             */
/*   Updated: 2019/04/21 19:46:31 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	int				i;
	unsigned char	*ptr;

	i = 0;
	if (!(ptr = malloc(size)))
		return (0);
	while (size--)
	{
		*ptr++ = '\0';
		i++;
	}
	return (ptr - i);
}
