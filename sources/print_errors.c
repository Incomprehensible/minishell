/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 07:36:01 by bomanyte          #+#    #+#             */
/*   Updated: 2019/08/05 07:53:44 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_err(int flag, char *error)
{
	if (flag == 1)
		no_matches_err(error);
	else if (flag == 2)
		parse_error(error);
	else if (flag == 3)
	{
		while (*error && *error != '=')
			error++;
		while (*error && *error == '=')
			error++;
		while (*error)
		{
			ft_putchar(*error);
			error++;
		}
		ft_putstr(" not found\n");
	}
}

void	print_err1(char *str)
{
	ft_putstr("cd: string not in pwd: ");
	ft_putstr(str);
	ft_putchar('\n');
}

void	print_err2(char *str)
{
	ft_putstr("minishell");
	ft_putstr(": ");
	ft_putstr(str);
	ft_putstr(": no arguments specified.\n");
}

void	print_err3(char *str, char *str1)
{
	ft_putstr("minishell");
	ft_putstr(": ");
	ft_putstr(str);
	ft_putstr(": no matches found: ");
	ft_putstr(str1);
	ft_putchar('\n');
}

int		print_err4(char *str)
{
	ft_putstr(str);
	ft_putstr(": command couldn't be executed because an error occured.\n");
	return (1);
}
