/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_legit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 07:27:29 by bomanyte          #+#    #+#             */
/*   Updated: 2019/08/07 12:04:50 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			is_valid_path(char *path, char *name)
{
	DIR *dir;

	if (!path || ((dir = opendir(path)) == NULL))
	{
		if (path && name)
		{
			ft_putstr("cd: ");
			if (access(path, F_OK) == -1)
				ft_putstr("no such file or directory: ");
			else if (access(path, R_OK) == -1)
				ft_putstr("permission denied: ");
			else
				ft_putstr("not a directory: ");
			ft_putstr(name);
			ft_putchar('\n');
		}
		return (0);
	}
	closedir(dir);
	return (1);
}

int			is_first_num(char *str)
{
	if (str[0] >= 48 && str[0] <= 57)
	{
		not_found_err(str);
		return (0);
	}
	return (1);
}

static int	is_regex(char c)
{
	if (c == '=' || c == '&' || c == '*' || c == '$' || c == '|')
	{
		if (c == '*')
			return (1);
		else
			return (2);
	}
	return (0);
}

int			is_legit(char *arr, t_env *env)
{
	int flag;
	int j;

	j = 0;
	if (arr && arr[j])
	{
		if ((flag = is_regex(arr[j])) > 0)
		{
			ft_putstr("minishell");
			print_err(flag, arr);
			return (0);
		}
		while (arr[j] && arr[j] != '=')
			j++;
		if (!arr[j])
			return (0);
		j++;
		if (arr[j] == '=')
		{
			ft_putstr(pull_env("PS1", env));
			print_err(3, arr);
			return (0);
		}
	}
	return (1);
}

int			wanna_set(char *str)
{
	int j;

	j = 0;
	if (str && str[j])
	{
		while (str[j] && str[j] != '=')
			j++;
		if (!str[j])
			return (0);
	}
	return (1);
}
