/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 14:56:12 by bomanyte          #+#    #+#             */
/*   Updated: 2019/04/20 22:54:20 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	int		i;
	char	*ss;

	i = 0;
	if (!(s) || !(len))
	{
		ss = ft_strnew(0);
		return (ss);
	}
	if (!(ss = (char *)ft_memalloc(len + 1)))
		return (0);
	while (len--)
		ss[i++] = s[start++];
	return (ss);
}
