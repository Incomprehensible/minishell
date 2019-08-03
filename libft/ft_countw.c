/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 20:20:18 by bomanyte          #+#    #+#             */
/*   Updated: 2019/04/21 20:21:23 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	ft_countw(const char *str, char del)
{
	int count;
	int flag;

	count = 0;
	flag = 0;
	while (*str != '\0' && (*str == del || *str == '\t'))
		str++;
	while (*str != '\0')
	{
		while (*str && *str != del && *str != '\t' && (flag = 1))
			str++;
		if (((*str == del || *str == '\t') && flag) || (!(*str) && flag))
		{
			count++;
			flag = 0;
		}
		while (*str == del || *str == '\t')
			str++;
	}
	return (count);
}
