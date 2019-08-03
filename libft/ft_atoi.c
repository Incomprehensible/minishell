/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 09:56:40 by bomanyte          #+#    #+#             */
/*   Updated: 2019/04/23 17:55:04 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	long long	res;
	int			sign;

	res = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '+' || (*str == '-' && (sign = -1)))
		str++;
	while (*str == '0')
		str++;
	while (*str >= 48 && *str <= 57)
	{
		res = res * 10 + *str++ - '0';
		if ((res != res * 10 / 10) && sign == 1)
			return (-1);
		else if ((res != res * 10 / 10) && sign == -1)
			return (0);
	}
	return (res * sign);
}
