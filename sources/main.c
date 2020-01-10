/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 07:26:38 by bomanyte          #+#    #+#             */
/*   Updated: 2019/08/07 12:04:50 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*is_ps1(t_env *env)
{
	while (env && ft_strcmp("PS1", env->name))
		env = env->next;
	if (!env)
		return (NULL);
	return (env);
}

void	display_prompt(t_env *home)
{
	static char *buf;
	static char c;

	if (home != NULL)
	{
		buf = home->value;
		ft_putstr(buf);
		c = '\0';
	}
	else
	{
		if (c == '\0')
			ft_putstr(buf);
		else
			ft_putstr("$> ");
	}
}

int		not_tabs(char **arr)
{
	int i;
	int j;
	int flag;

	i = 0;
	j = 0;
	flag = 0;
	while (arr[i])
	{
		while (arr[i][j])
		{
			if (arr[i][j] != ' ' && arr[i][j] != '\t')
				flag = 1;
			j++;
		}
		i++;
		j = 0;
	}
	return (flag);
}

int		ft_cleanall(t_env *env, char **history, char *line)
{
	t_env *tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		ft_strdel(&tmp->name);
		if (tmp->value)
			ft_strdel(&tmp->value);
		free(tmp);
	}
	if (line)
		ft_strdel(&line);
	ft_arrmemdel((void **)history);
	return (0);
}

int		main(int hist, char **arr, char **env)
{
	char	*str;
	char	**history;
	t_env	*envr;

	hist = 0;
	envr = get_envars(env);
	history = create_hist();
	while (1)
	{
		display_prompt(is_ps1(envr));
		signal(SIGINT, sig_handleout);
		get_next_line(0, &str);
		hist = ft_add_history(history, str, hist);
		if (!ft_strcmp(str, "exit"))
			break ;
		if (str && *str)
		{
			arr = ft_strsplit(str, ' ');
			if (*arr && not_tabs(arr))
				get_command(arr, envr, history);
			ft_arrmemdel((void **)arr);
		}
		ft_strdel(&str);
	}
	return (ft_cleanall(envr, history, str));
}
