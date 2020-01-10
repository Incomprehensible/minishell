/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 21:38:14 by bomanyte          #+#    #+#             */
/*   Updated: 2019/08/05 08:14:28 by bomanyte         ###   ########.fr       */
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
		while (ss[j] == ch || ss[j] == '\t')
			j++;
		while (!(ss[j] == ch) && !(ss[j] == '\t') && ss[j])
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

static	char		*ft_splitter(const char *s, char d, int n, int l)
{
	char	*ptr;
	int		f;
	int		k;

	f = 0;
	k = 0;
	if (!(ptr = (char *)malloc(sizeof(char) * (l + 1))))
		return (0);
	l = 0;
	while (!(k) && (*s != '\0'))
	{
		while (*s != '\0' && (*s == d || *s == '\t'))
			s++;
		while (l != n && *s && (*s != d && *s != '\t' && (f = 1)))
			s++;
		while (l == n && *s && *s != d && *s != '\t' && !f && ++k)
			*ptr++ = *s++;
		if (l != n && (((*s == d || *s == '\t') && f) || (!(*s) && f)))
		{
			l++;
			f = 0;
		}
	}
	return (ptr - k);
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
