/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envar_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 07:31:21 by bomanyte          #+#    #+#             */
/*   Updated: 2019/08/05 07:49:22 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_env(char *var, t_env *env, char *new)
{
	char path[PATH_MAX];

	if (!ft_strcmp(var, "PWD"))
	{
		getcwd(path, sizeof(path));
		new = ft_strdup(path);
	}
	while (env && ft_strcmp(env->name, var))
		env = env->next;
	if (env)
	{
		if (env->value)
			free(env->value);
		env->value = new;
	}
	else
		free(new);
}

char	*pull_env(char *var, t_env *env)
{
	while (env && ft_strcmp(env->name, var) != 0)
		env = env->next;
	if (!env)
		return (0);
	return (env->value);
}

char	*parse_env(char **env, int row)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (env[row][i] != '=')
		i++;
	i++;
	j = i;
	while (env[row][j] && env[row][j] != '\n')
		j++;
	str = (char *)ft_memalloc(j - i + 1);
	j = 0;
	while (env[row][i])
	{
		str[j] = env[row][i];
		j++;
		i++;
	}
	return (str);
}

char	*parse_name(char **env, int row)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	while (env[row][i] != '=')
		i++;
	str = (char *)ft_memalloc(i + 1);
	while (j != i)
	{
		str[j] = env[row][j];
		j++;
	}
	return (str);
}
