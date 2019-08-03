/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 19:21:53 by bomanyte          #+#    #+#             */
/*   Updated: 2019/04/21 19:44:38 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_mynum(int nb, int res)
{
	if (nb < 0)
	{
		if (nb == -2147483648)
		{
			res = res + 1;
			nb = 147483648;
		}
		else
			nb = -nb;
	}
	else if (nb > 9)
		nb = nb / 10;
	else if (nb <= 9)
		return (res);
	res = ft_mynum(nb, res + 1);
	return (res);
}

char		*ft_itoa(int n)
{
	int		len;
	char	*str;
	int		trigger;

	trigger = 0;
	if (!(len = ft_mynum(n, 1)))
		return (0);
	if (!(str = (char *)ft_memalloc(len + 1)))
		return (0);
	if (n < 0 && (trigger = 1))
	{
		str[0] = '-';
		if (n == -2147483648 && (n = 147483648) && (trigger += 1))
			str[1] = '2';
		else
			n = n * -1;
	}
	while (len-- > trigger)
	{
		str[len] = (n % 10) + '0';
		n = n / 10;
	}
	return (str);
}
