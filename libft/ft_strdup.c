/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 04:03:27 by bomanyte          #+#    #+#             */
/*   Updated: 2019/04/19 20:12:20 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		sz;
	char	*ptr;

	sz = 0;
	while (s1[sz] != '\0')
		sz++;
	if (!(ptr = (char *)ft_memalloc(sz + 1)))
		return (0);
	while (*s1 != '\0')
		*ptr++ = *s1++;
	return (ptr - sz);
}
