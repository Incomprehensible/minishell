/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 07:28:18 by bomanyte          #+#    #+#             */
/*   Updated: 2019/08/05 07:28:21 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		colorize(char *str)
{
	static int i;
	static int color;

	if (i == 666)
	{
		color++;
		if (color == 6)
			color = 1;
		ft_putstr("\033[");
		ft_putnbr(30 + color);
		ft_putstr("m");
		return (1);
	}
	else
	{
		i = ft_strcmp(str, "colorize");
		color = 1;
		if (!i)
		{
			i = 666;
			ft_putstr("\033[36m");
			return (1);
		}
	}
	return (0);
}
