/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 13:45:01 by bomanyte          #+#    #+#             */
/*   Updated: 2019/04/19 20:25:57 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		i;
	char	*cp;

	i = 0;
	if (!(s) || !(f))
		return (0);
	while (s[i] != '\0')
		i++;
	if (!(cp = (char *)ft_memalloc(i + 1)))
		return (0);
	while (--i >= 0)
		cp[i] = f(s[i]);
	return (cp);
}
