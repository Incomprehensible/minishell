/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 12:28:40 by bomanyte          #+#    #+#             */
/*   Updated: 2019/04/14 22:50:27 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char const *s, int fd)
{
	char c;

	while (*s)
	{
		c = *s;
		write(fd, &c, 1);
		s++;
	}
	write(fd, "\n", 1);
}
