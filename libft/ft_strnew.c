/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 23:00:11 by bomanyte          #+#    #+#             */
/*   Updated: 2019/04/23 17:53:08 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	int		i;
	char	*str;

	i = 0;
	if (size == (size_t)-1)
		return (0);
	if (!(str = (char*)malloc(size + 1)))
		return (0);
	str[size] = '\0';
	while (size-- && (i = i + 1))
		*str++ = '\0';
	return (str - i);
}
