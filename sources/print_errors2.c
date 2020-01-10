/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errors2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 07:32:53 by bomanyte          #+#    #+#             */
/*   Updated: 2019/08/05 07:32:56 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*access_err(char *command)
{
	ft_putstr(command);
	ft_putstr(": access denied\n");
	return ("\0");
}

void	parse_error(char *error)
{
	ft_putstr(": parse error near '");
	while (*error && *error != '=')
	{
		ft_putchar(*error);
		error++;
	}
	ft_putstr("'\n");
}

void	no_matches_err(char *error)
{
	ft_putstr(": no matches found: ");
	ft_putstr(error);
	ft_putchar('\n');
}

void	not_found_err(char *command)
{
	ft_putstr("minishell: command not found: ");
	ft_putstr(command);
	ft_putchar('\n');
}
