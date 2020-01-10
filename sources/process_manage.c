/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_manage.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 07:33:36 by bomanyte          #+#    #+#             */
/*   Updated: 2019/08/05 10:45:32 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		count_commands(char **arr)
{
	int	len;
	int i;
	int flag;
	int flag2;

	i = 0;
	len = 0;
	flag = 0;
	flag2 = 0;
	while (arr[i])
	{
		if (!flag && arr[i] && ft_strcmp(arr[i], ";"))
		{
			flag = 1;
			len++;
		}
		else if (arr[i] && !ft_strcmp(arr[i], ";"))
		{
			flag = 0;
			flag2 = 1;
		}
		if (arr[i])
			i++;
	}
	return (flag2 ? len : 0);
}

int		manage_local(t_env *env, char **arr, int i)
{
	while (arr[i] && wanna_set(arr[i]))
	{
		if (!is_legit(arr[i], env))
			return (-1);
		if (!is_first_num(arr[i]))
			return (-1);
		set_env(env, arr, i);
		i++;
	}
	return (i);
}

int		manage_global(t_env *env, char **arr, int i)
{
	while (arr[i] && ((!ft_strcmp(arr[i], "setenv") ||
					(!ft_strcmp(arr[i], "export")))))
	{
		i++;
		while (arr[i])
		{
			if (!is_legit(arr[i], env))
				return (-1);
			if (!is_first_num(arr[i]))
				return (-1);
			set_env(env, arr, i);
			i++;
		}
	}
	return (i);
}

int		manage_pid(char **arr, t_env *env, int i)
{
	pid_t	child_pid;
	char	*path;

	if ((path = is_command(arr, env, i)) == NULL)
		return (0);
	if (!(*path))
		return (1);
	child_pid = fork();
	signal(SIGINT, sig_handlein);
	if (child_pid == 0)
	{
		if ((execve(path, arr, NULL) == -1))
			exit(print_err4(arr[i]));
	}
	else if (child_pid < 0)
		ft_putstr("Fork failure\n");
	else
	{
		ft_strdel(&path);
		wait(&child_pid);
	}
	return (1);
}
