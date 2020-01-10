/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 07:29:46 by bomanyte          #+#    #+#             */
/*   Updated: 2019/08/05 07:46:10 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int					ft_add_history(char **hist, char *str, int i)
{
	colorize(str);
	if (!str || !*str)
		return (i);
	if (i < HISTSIZE)
		hist[i] = ft_strdup(str);
	else
	{
		i = 0;
		free(hist[i]);
		hist[i] = NULL;
		while (i + 1 != HISTSIZE)
		{
			hist[i] = hist[i + 1];
			i++;
		}
		hist[i] = ft_strdup(str);
	}
	return (++i);
}

static int			find_n_length(long long num)
{
	long long i;

	i = 1;
	while (num / 10 != 0)
	{
		num = num / 10;
		i++;
	}
	return (i);
}

static long long	history_size(char **history)
{
	long long i;

	i = 0;
	while (history[i])
		i++;
	return (i);
}

void				get_history(char **history)
{
	long long i;
	long long j;
	long long max;

	max = find_n_length(history_size(history));
	i = 0;
	while (history[i])
	{
		j = max;
		ft_putstr("	");
		ft_putnbr(i + 1);
		ft_putstr(":");
		if (find_n_length(i + 1) != max)
		{
			while (j--)
				ft_putstr(" ");
		}
		else
			ft_putstr(" ");
		ft_putstr(history[i]);
		write(1, "\n", 1);
		i++;
	}
}

char				**create_hist(void)
{
	char **hist;

	hist = (char **)ft_memalloc(sizeof(char *) * HISTSIZE + 1);
	return (hist);
}
