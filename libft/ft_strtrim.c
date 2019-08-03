/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 21:47:36 by bomanyte          #+#    #+#             */
/*   Updated: 2019/04/20 15:30:47 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		find_len(char const *str)
{
	int i;
	int flag;

	i = 0;
	flag = 0;
	while (str[i] != '\0')
	{
		if (!(str[i] == ' ' || str[i] == '\n' || str[i] == '\t'))
			flag += 1;
		i++;
	}
	if (!(flag))
		return (0);
	return (i);
}

static	int		find_strt(char const *str)
{
	int i;

	i = 0;
	while (str[i] != '\0' &&
			(str[i] == ' ' || str[i] == '\n' || str[i] == '\t'))
		i++;
	return (i);
}

static	int		find_fin(char const *str)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i + 1] != '\0')
		i++;
	while (str[i] != '\0' &&
			(str[i] == ' ' || str[i] == '\n' || str[i] == '\t'))
	{
		i--;
		count++;
	}
	return (count);
}

char			*ft_strtrim(char const *s)
{
	int		start;
	int		end;
	int		num;
	int		tmp;
	char	*ss;

	if (!(s))
		return (0);
	if (!(num = find_len(s)))
	{
		ss = ft_strnew(0);
		return (ss);
	}
	start = find_strt(s);
	end = find_fin(s);
	if (!(ss = (char *)ft_memalloc(num - (end + start) + 1)))
		return (0);
	tmp = num - end - 1;
	num = num - (end + start) - 1;
	while (tmp >= start)
		ss[num--] = s[tmp--];
	return (ss);
}
