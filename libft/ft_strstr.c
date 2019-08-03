/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 08:38:57 by bomanyte          #+#    #+#             */
/*   Updated: 2019/04/19 21:31:15 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strstr(const char *haystack, const char *needle)
{
	int k;
	int j;

	k = 0;
	j = 0;
	if (!(*needle))
		return ((char *)haystack);
	while (*haystack != '\0' && *needle != '\0')
	{
		k = 0;
		j = 0;
		while (*haystack != '\0' && *haystack != *needle)
			haystack++;
		while (*haystack && *haystack == *needle && haystack++ && needle++)
		{
			k++;
			j++;
			if (*needle == '\0')
				return ((char *)haystack - k);
		}
		if (*haystack)
			haystack = haystack - k + 1;
		needle = needle - j;
	}
	return (0);
}
