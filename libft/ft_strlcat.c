/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 06:13:15 by bomanyte          #+#    #+#             */
/*   Updated: 2019/04/23 21:46:48 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	char	*s;
	size_t	k;
	size_t	i;

	i = 0;
	k = size;
	s = (char *)src;
	while (*dst && size--)
	{
		dst++;
		i++;
	}
	if (!(k - i))
		return (k + (ft_strlen(src)));
	k = k - i;
	while (*s && k != 1)
	{
		*dst++ = *s++;
		k--;
	}
	*dst = '\0';
	return (i + (ft_strlen(src)));
}
