/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 02:55:52 by bomanyte          #+#    #+#             */
/*   Updated: 2019/08/07 12:04:50 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		exec_one(char **comm, t_env *env, char **hist)
{
	int i;
	int j;

	i = 0;
	if (one_time_command(comm, env, hist))
		return ;
	i = manage_local(env, comm, i);
	if (i == -1)
		return ;
	j = i;
	i = manage_global(env, comm, i);
	if (j < i || i == -1)
		return ;
	if (comm[i] && !ft_strcmp(comm[i], "cd"))
		manage_cd(comm, env, i);
	else
	{
		j = 0;
		if (i > j)
			subst_comm(comm, i, j);
		if (comm[0] && !manage_pid(comm, env, 0))
			not_found_err(comm[0]);
	}
}

static char		***create_triple(char **arr)
{
	char	***to_exec;
	int		len;

	len = count_commands(arr);
	to_exec = (char ***)malloc(sizeof(char **) * len + 1);
	to_exec[len] = NULL;
	return (to_exec);
}

static void		fill_arr(char **to, char **from, int i, int s)
{
	int len;

	len = 0;
	while (len != i)
	{
		to[len] = ft_strdup(from[s]);
		len++;
		s++;
	}
	to[len] = NULL;
}

static char		***make_commands(char **arr)
{
	char	***to_exec;
	int		len;
	int		i;
	int		len2;

	i = 0;
	to_exec = create_triple(arr);
	len = 0;
	while (arr[i])
	{
		len2 = 0;
		while (arr[i] && !ft_strcmp(arr[i], ";"))
			i++;
		if (!arr[i])
			return (to_exec);
		while (arr[i] && ft_strcmp(arr[i], ";"))
		{
			i++;
			len2++;
		}
		to_exec[len] = (char **)malloc(sizeof(char *) * len2 + 1);
		fill_arr(to_exec[len], arr, len2, i - len2);
		len++;
	}
	return (to_exec);
}

int				exec_many(char **arr, t_env *env, char **hist)
{
	char	***cmms;
	int		i;

	i = 0;
	if (!count_commands(arr))
		return (0);
	cmms = make_commands(arr);
	while (cmms && cmms[i])
	{
		exec_one(cmms[i], env, hist);
		i++;
	}
	i = 0;
	while (cmms && cmms[i])
	{
		if (cmms[i])
			ft_arrmemdel((void **)cmms[i]);
		i++;
	}
	if (cmms)
		free(cmms);
	return (1);
}
