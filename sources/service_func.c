/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   service_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 07:34:22 by bomanyte          #+#    #+#             */
/*   Updated: 2019/08/05 07:55:35 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_ps1(char **arr)
{
	int i;

	i = 0;
	if (!ft_strcmp("setenv", arr[0]) || !ft_strcmp("export", arr[0])
		|| (arr[1] && !ft_strcmp(arr[1], "PS1")))
		i = 1;
	return (i);
}

void	set_ps1(t_env *tmp)
{
	tmp->next = (t_env *)malloc(sizeof(t_env));
	tmp = tmp->next;
	tmp->name = ft_strdup("PS1");
	tmp->value = ft_strdup("$> ");
	tmp->id = 0x0;
	tmp->next = NULL;
}

int		ft_counts(char **env)
{
	int i;

	i = 0;
	while (env[i])
		i++;
	return (--i);
}

char	*get_start(char **arr, int i)
{
	char *start;

	start = NULL;
	if ((arr[i][0] == '\'' || arr[i][0] == '\"') && arr[i][1])
		start = &arr[i][1];
	return (start);
}

char	*get_finish(char **arr, int i)
{
	char *finish;

	finish = NULL;
	if ((ft_strlen(arr[i]) > 2 &&
		(arr[i][ft_strlen(arr[i]) - 1] == '\''
			|| arr[i][ft_strlen(arr[i]) - 1] == '\"')))
		finish = &arr[i][ft_strlen(arr[i]) - 1];
	return (finish);
}
