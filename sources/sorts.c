/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorts.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 07:35:03 by bomanyte          #+#    #+#             */
/*   Updated: 2019/08/05 07:56:32 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	subst_comm(char **comm, int i, int j)
{
	while (comm[j] && comm[i])
	{
		if (comm[j])
			free(comm[j]);
		comm[j++] = ft_strdup(comm[i++]);
	}
	while (comm[j])
	{
		if (comm[j])
			free(comm[j]);
		comm[j++] = NULL;
	}
}

void	clear_env(t_env *tmp1, t_env *env)
{
	t_env *tmp2;

	tmp2 = env->next;
	free(env->name);
	if (env->value)
		free(env->value);
	free(env);
	tmp1->next = tmp2;
}

t_env	*sort_global(t_env *env)
{
	t_env *tmp;

	while (env->next && env->next->id)
		env = env->next;
	tmp = env->next;
	env->next = (t_env *)malloc(sizeof(t_env));
	env = env->next;
	env->next = tmp;
	return (env);
}

t_env	*sort_local(t_env *env)
{
	while (env->next)
		env = env->next;
	env->next = (t_env *)malloc(sizeof(t_env));
	env = env->next;
	env->id = 0x0;
	env->next = NULL;
	return (env);
}
