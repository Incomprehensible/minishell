/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 07:25:25 by bomanyte          #+#    #+#             */
/*   Updated: 2019/08/07 11:22:43 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*makepath(char *buf, char *plus, t_env *env)
{
	char *path;
	char *tmp;

	if (plus && *plus && plus[0] == '~' && plus[1] && plus[1] == '/')
	{
		while (env && ft_strcmp("HOME", env->name))
			env = env->next;
		if (!env)
			return (NULL);
		tmp = ft_strjoin(env->value, "/");
		path = ft_strjoin(tmp, plus + 2);
	}
	else
	{
		tmp = ft_strjoin(buf, "/");
		path = ft_strjoin(tmp, plus);
	}
	free(tmp);
	return (path);
}

static int	cd_home(char **arr, t_env *env, int i)
{
	char buf[PATH_MAX];
	char *path;

	if (!arr[i + 1] || !ft_strcmp("$HOME", arr[i + 1])
			|| !ft_strcmp(arr[i + 1], "~"))
	{
		path = pull_env("HOME", env);
		if (path && !is_valid_path(path, path))
			return (1);
		if (path)
		{
			if (pull_env("OLDPWD", env))
				change_env("OLDPWD", env, ft_strdup(getcwd(buf, sizeof(buf))));
		}
		path == NULL ? ft_putstr("$HOME isn't set.\n")
			: chdir(path);
		return (1);
	}
	return (0);
}

static void	manage_path(char *str, t_env *env)
{
	char buf[PATH_MAX];
	char *path;

	getcwd(buf, sizeof(buf));
	path = is_valid_path(str, NULL) ? ft_strdup(str) : makepath(buf, str, env);
	if (is_valid_path(path, str))
	{
		change_env("OLDPWD", env, ft_strdup(buf));
		chdir(path);
		if (path)
			ft_strdel(&path);
	}
	else
		ft_strdel(&path);
}

static void	manage_oldpwd(t_env *env)
{
	char *path;

	path = ft_strdup(pull_env("PWD", env));
	ft_putchar('~');
	ft_putstr(pull_env("OLDPWD", env));
	ft_putchar('\n');
	change_env("OLDPWD", env, path);
}

void		manage_cd(char **arr, t_env *env, int i)
{
	if (!ft_strcmp(arr[i], "cd"))
	{
		if (!cd_home(arr, env, i))
		{
			if (arr[i + 2])
			{
				print_err1(arr[i + 1]);
				return ;
			}
			if (ft_strcmp(arr[i + 1], "-"))
				manage_path(arr[i + 1], env);
			else
			{
				if (chdir(pull_env("OLDPWD", env)))
				{
					ft_putstr("$OLDPWD isn't set.\n");
					return ;
				}
				manage_oldpwd(env);
			}
		}
	}
	change_env("PWD", env, NULL);
}
