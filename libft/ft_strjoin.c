/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 23:44:29 by bomanyte          #+#    #+#             */
/*   Updated: 2019/04/21 19:56:02 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	j = 0;
	if (!(s1) || !(s2))
		return (0);
	while (s1[i])
		i++;
	while (s2[j])
		j++;
	if (!(s = (char *)ft_memalloc(i + j + 1)))
		return (0);
	while (*s1)
		*s++ = *s1++;
	while (*s2)
		*s++ = *s2++;
	return (s - (i + j));
}
