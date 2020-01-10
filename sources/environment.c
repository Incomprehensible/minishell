/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 07:32:09 by bomanyte          #+#    #+#             */
/*   Updated: 2019/08/05 07:51:32 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	list_env(t_env *env)
{
	while (env)
	{
		if (env->value && env->id)
		{
			ft_putstr(env->name);
			ft_putchar('=');
			ft_putstr(env->value);
			ft_putchar('\n');
		}
		env = env->next;
	}
}

int		unset_env(t_env *env, char *var)
{
	t_env *tmp1;

	while (env && ft_strcmp(env->name, var))
	{
		tmp1 = env;
		env = env->next;
	}
	if (env && ft_strcmp(var, "PS1"))
	{
		clear_env(tmp1, env);
		return (1);
	}
	else if (env && env->id)
	{
		if (env->value)
			free(env->value);
		env->value = ft_strdup("$> ");
		env->id = 0x0;
		return (1);
	}
	return (0);
}

void	set_env(t_env *env, char **arr, int ind)
{
	int		i;
	char	*name;
	char	*value;

	i = check_ps1(arr);
	name = parse_name(arr, ind);
	value = parse_env(arr, ind);
	if (!pull_env(name, env))
	{
		env = i ? sort_global(env) : sort_local(env);
		env->name = name;
	}
	else
	{
		while (env && ft_strcmp(env->name, name))
			env = env->next;
		if (env && env->value)
			ft_strdel(&env->value);
		ft_strdel(&name);
	}
	env->id = i ? 0x1 : 0x0;
	env->value = value;
}

void	get_nameval(t_env *start, char **env)
{
	int		i;
	int		ps1;
	t_env	*tmp;

	i = 0;
	ps1 = 0;
	while (start)
	{
		start->name = parse_name(env, i);
		start->value = parse_env(env, i);
		start->id = (char)0x1;
		if (!ft_strcmp(start->name, "PS1"))
			ps1 = 1;
		i++;
		tmp = start;
		start = start->next;
	}
	if (!ps1)
		set_ps1(tmp);
}

t_env	*get_envars(char **env)
{
	int		rows;
	t_env	*envar;
	t_env	*start;

	rows = ft_counts(env);
	envar = (t_env *)malloc(sizeof(t_env));
	start = envar;
	envar->name = NULL;
	envar->value = NULL;
	envar->next = NULL;
	while (--rows)
	{
		envar->next = (t_env *)malloc(sizeof(t_env));
		envar = envar->next;
		envar->name = NULL;
		envar->value = NULL;
		envar->next = NULL;
	}
	get_nameval(start, env);
	return (start);
}
