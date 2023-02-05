/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anollero <anollero@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 13:54:32 by anollero          #+#    #+#             */
/*   Updated: 2023/02/05 13:55:57 by anollero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"

int	ft_sizehex(unsigned long long num)
{
	int	size;

	size = 0;
	while (num != 0)
	{
		num = num / 16;
		size++;
	}
	return (size);
}

char	*ft_atoh(unsigned long long num, int mode)
{
	char	*str;
	char	*hex;
	int		i;

	i = ft_sizehex(num) - 1;
	hex = "0123456789abcdef";
	if (num == 0)
	{
		str = ft_calloc(2, 1);
		str[0] = '0';
		return (str);
	}
	str = ft_calloc(ft_sizehex(num) + 1, 1);
	while (num != 0)
	{
		str[i] = hex[num % 16];
		if (mode == 1)
			str[i] = ft_toupper(str[i]);
		i--;
		num = num / 16;
	}
	return (str);
}
