/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 15:46:51 by bomanyte          #+#    #+#             */
/*   Updated: 2019/08/06 13:51:02 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

char	*ft_strndup(const char *s1, char n)
{
	int		sz;
	char	*ptr;

	sz = 0;
	while (s1[sz] != n)
		sz++;
	if (!(ptr = (char *)ft_memalloc(sz + 1)))
		return (0);
	while (*s1 != n)
		*ptr++ = *s1++;
	return (ptr - sz);
}

char	*ft_joinfree(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*s;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = (char *)s1;
	if (!(s1) || !(s2))
		return (0);
	while (s1[i])
		i++;
	while (s2[j])
		j++;
	if (!(s = (char *)ft_memalloc(i + j + 1)))
	{
		ft_strdel(&tmp);
		return (0);
	}
	while (*s1)
		*s++ = *s1++;
	while (*s2)
		*s++ = *s2++;
	ft_strdel(&tmp);
	return (s - (i + j));
}

char	*ft_update(char *str, int fd, char **table, int i)
{
	if (i)
	{
		if (!table[fd])
		{
			if (!(table[fd] = ft_strnew(1)))
				return (0);
		}
		return (table[fd]);
	}
	ft_strdel(&table[fd]);
	if (str)
		table[fd] = str;
	return (table[fd]);
}

char	*ft_cut(char *s, char **table, int fd)
{
	size_t	i;
	char	*new;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i])
	{
		if (!(new = ft_strndup(s, '\n')))
			ft_update(0, fd, table, 0);
		ft_update(ft_strdup(s + (++i)), fd, table, 0);
	}
	else
	{
		new = ft_strdup(s);
		ft_update(0, fd, table, 0);
	}
	return (new);
}

int		get_next_line(int fd, char **line)
{
	int				j;
	static char		*table[MAX_FD];
	char			buf[BUFF_SIZE + 1];

	if (fd < 0 || !line || fd > MAX_FD || read(fd, buf, 0) < 0)
		return (-1);
	if (!(ft_update(table[fd], fd, table, 1)))
		return (0);
	while ((j = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[j] = '\0';
		if (!(table[fd] = ft_joinfree(table[fd], buf)))
			return (-1);
		if (ft_strchr(table[fd], '\n') != 0)
			break ;
	}
	if (!*table[fd])
		return (0);
	if (!(*line = ft_cut(table[fd], table, fd)))
		return (-1);
	return (1);
}
