/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anollero <anollero@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:26:26 by anollero          #+#    #+#             */
/*   Updated: 2022/10/09 15:13:11 by anollero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_min(size_t x, size_t y)
{
	if (x > y)
		return (y);
	else
		return (x);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	count;
	size_t	srccount;
	size_t	ret;

	srccount = 0;
	count = ft_strlen(dst);
	ret = count;
	if (size == 0)
		return (ft_strlen(src) + ft_min(size, ret));
	if (ft_strlen(dst) > size)
		return (ft_strlen(src) + ft_min(size, ret));
	while (src[srccount] != '\0' && count < size - 1)
	{
		dst[count] = src[srccount];
		srccount++;
		count++;
	}
	dst[count] = '\0';
	return (ft_strlen(src) + ft_min(size, ret));
}
