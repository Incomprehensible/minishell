/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 21:38:14 by bomanyte          #+#    #+#             */
/*   Updated: 2019/04/23 16:15:49 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int			ft_countch(const char *ss, char ch, int num)
{
	int		len;
	int		j;
	int		n;
	int		ind;

	j = 0;
	n = 0;
	len = 0;
	ind = 0;
	while (ss[j] != '\0' && !ind)
	{
		while (ss[j] == ch)
			j++;
		while (!(ss[j] == ch) && ss[j])
		{
			if (n == num - 1 && (ind = 1))
				len++;
			j++;
		}
		if (ss[j] == '\0')
			return (len);
		n++;
		j++;
	}
	return (len);
}

static	char		*ft_splitter(const char *sss, char del, int n, int len)
{
	char	*ptr;
	int		flag;
	int		flag2;

	flag = 0;
	flag2 = 0;
	if (!(ptr = (char *)malloc(sizeof(char) * (len + 1))))
		return (0);
	len = 0;
	while (!(flag2) && (*sss != '\0'))
	{
		while (*sss != '\0' && *sss == del)
			sss++;
		while (len != n && *sss && (*sss != del && (flag = 1)))
			sss++;
		while (len == n && *sss && *sss != del && !flag && ++flag2)
			*ptr++ = *sss++;
		if (len != n && ((*sss == del && flag) || (!(*sss) && flag)))
		{
			len++;
			flag = 0;
		}
	}
	return (ptr - flag2);
}

char				**ft_strsplit(const char *s, char c)
{
	int		i;
	int		count;
	char	**mom;
	int		len;

	i = 0;
	if (!s || !c)
		return (0);
	count = ft_countw(s, c);
	mom = (char **)malloc(sizeof(mom) * (count + 1));
	if (!(mom))
		return (0);
	mom[count] = NULL;
	while (i < count)
	{
		len = ft_countch(s, c, i + 1);
		mom[i] = ft_splitter(s, c, i, len);
		if (!(mom[i]))
			return (ft_arrmemdel((void **)mom));
		mom[i][len] = '\0';
		i++;
	}
	return (mom);
}
