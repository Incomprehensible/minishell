/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_manage.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 07:29:03 by bomanyte          #+#    #+#             */
/*   Updated: 2019/08/07 12:04:50 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*search_command(char **paths, char *command, t_env *env)
{
	int		i;
	char	*full;

	i = 0;
	if (!paths)
		return (NULL);
	full = makepath(paths[0], command, env);
	while (paths[i] && (access(full, 0)))
	{
		free(full);
		full = makepath(paths[i], command, env);
		i++;
	}
	if (!paths[i])
	{
		free(full);
		return (NULL);
	}
	if (access(full, 1))
	{
		free(full);
		return (access_err(command));
	}
	return (full);
}

char		*command_path(t_env *env, char *str)
{
	char *p;
	char **paths;

	p = pull_env("PATH", env);
	paths = ft_strsplit(p, ':');
	if ((!access(str, 0) && !access(str, 1)))
		p = ft_strdup(str);
	else
		p = search_command(paths, str, env);
	if (paths)
		ft_arrmemdel((void **)paths);
	return (p);
}

char		*is_command(char **arr, t_env *env, int ind)
{
	char path[PATH_MAX];
	char *p;

	if (arr[ind][0] == '.' && arr[ind][1] == '/')
	{
		getcwd(path, sizeof(path));
		p = makepath(path, arr[0], NULL);
		if (!access(p, 0))
		{
			if (!access(p, 1))
				return (p);
			else
			{
				free(p);
				return (access_err(arr[ind]));
			}
		}
	}
	p = command_path(env, arr[ind]);
	return (p);
}

int			one_time_command(char **arr, t_env *env, char **hist)
{
	if (!ft_strcmp(arr[0], "colorize"))
		colorize(arr[0]);
	else if (!ft_strcmp(arr[0], "history"))
		get_history(hist);
	else if (!ft_strcmp(arr[0], "env") || !ft_strcmp(arr[0], "/usr/bin/env"))
		list_env(env);
	else if (!ft_strcmp(arr[0], "unsetenv"))
	{
		if (!arr[1])
			print_err2(arr[0]);
		else if (!unset_env(env, arr[1]))
			print_err3(arr[0], arr[1]);
	}
	else if (!ft_strcmp(arr[0], "echo"))
	{
		if (arr[1] && arr[1][0] == '$' && arr[1][1])
			echo_var(env, arr[1]);
		else
			echo_this(arr);
	}
	else
		return (0);
	return (1);
}

void		get_command(char **arr, t_env *env, char **hist)
{
	int i;
	int j;

	i = 0;
	if (exec_many(arr, env, hist) || one_time_command(arr, env, hist))
		return ;
	i = manage_local(env, arr, i);
	if (i == -1)
		return ;
	j = i;
	i = manage_global(env, arr, i);
	if (j < i || i == -1)
		return ;
	if (arr[i] && !ft_strcmp(arr[i], "cd"))
		manage_cd(arr, env, i);
	else
	{
		j = 0;
		if (i > j)
			subst_comm(arr, i, j);
		if (arr[0] && !manage_pid(arr, env, 0))
			not_found_err(arr[0]);
	}
}
