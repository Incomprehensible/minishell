/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 15:28:09 by bomanyte          #+#    #+#             */
/*   Updated: 2019/04/23 15:21:50 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	size_t			i;
	unsigned char	*p;
	unsigned char	*copy;
	t_list			*tmp;

	i = 0;
	p = (unsigned char *)content;
	if (!(copy = ft_memalloc(sizeof(unsigned char) * content_size)))
		return (0);
	if ((!(p) || !(content_size)))
	{
		copy = NULL;
		content_size = 0;
	}
	while ((copy && p[i] && i < content_size - 1) && (copy[i] = p[i]))
		i++;
	if (!(tmp = (t_list *)malloc(sizeof(t_list))))
	{
		free(copy);
		return (0);
	}
	tmp->content = (void *)copy;
	tmp->content_size = content_size;
	tmp->next = NULL;
	return (tmp);
}
