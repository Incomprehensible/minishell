/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandlers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 00:52:58 by bomanyte          #+#    #+#             */
/*   Updated: 2019/08/05 07:12:42 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handlein(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		signal(SIGINT, sig_handlein);
	}
}

void	sig_handleout(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr("\n");
		display_prompt(NULL);
		signal(SIGINT, sig_handleout);
	}
}
