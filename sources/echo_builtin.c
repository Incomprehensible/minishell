/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 07:30:35 by bomanyte          #+#    #+#             */
/*   Updated: 2019/08/05 07:47:35 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			echo_var(t_env *env, char *var)
{
	char *str;

	str = var + 1;
	while (env && ft_strcmp(env->name, str))
		env = env->next;
	if (env)
		ft_putstr(env->value);
	write(1, "\n", 1);
}

static void		echo_str(char *start, char *finish)
{
	while (start != finish)
	{
		ft_putchar(*start);
		start++;
	}
}

static int		echo_that(char *str)
{
	int words;
	int brackets;
	int i;

	i = 0;
	brackets = 0;
	if (!str || !*str)
		return (0);
	words = ft_countw(str, ' ');
	while (str[i])
	{
		if (*str == '\'' || *str == '\"')
			brackets++;
		i++;
	}
	if (brackets == words * 2)
		return (0);
	while (*str)
	{
		if (*str != '\'' && *str != '\"')
			ft_putchar(*str);
		str++;
	}
	return (1);
}

void			echo_this(char **arr)
{
	int		i;
	char	*start;
	char	*finish;

	i = 1;
	while (arr[1] && arr[i])
	{
		if (!echo_that(arr[i]))
		{
			start = get_start(arr, i);
			finish = get_finish(arr, i);
			if (!start || !finish)
			{
				start = &arr[i][0];
				finish = &arr[i][ft_strlen(arr[i])];
			}
			echo_str(start, finish);
		}
		i++;
		if (arr[i])
			write(1, " ", 1);
	}
	write(1, "\n", 1);
}
