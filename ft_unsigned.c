/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anollero <anollero@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 13:31:53 by anollero          #+#    #+#             */
/*   Updated: 2023/02/05 13:52:44 by anollero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"

char	*ft_utoa_aux(void)
{
	char	*res;

	res = (char *)malloc(2);
	if (res == NULL)
		return (NULL);
	res[0] = 48;
	res[1] = '\0';
	return (res);
}

void	ft_sign_ualloc(unsigned int *aux, char *sign, int *alloc)
{
	*(alloc) = 1;
	*(sign) = '\0';
	while (*aux != 0)
	{
		*aux = *(aux) / 10;
		*(alloc) = *(alloc) + 1;
	}
}

char	*ft_utoa(unsigned int n)
{
	char			sign;
	int				alloc;
	unsigned int	aux;
	char			*res;

	aux = n;
	if (n == 0)
		return (ft_utoa_aux());
	ft_sign_ualloc(&aux, &sign, &alloc);
	res = (char *)malloc(alloc * sizeof(char));
	if (res == NULL)
		return (NULL);
	aux = n;
	res[alloc - 1] = '\0';
	alloc = alloc - 2;
	while (aux != 0)
	{
		res[alloc] = (aux % 10) + 48;
		aux = aux / 10;
		alloc--;
	}
	if (sign == '-')
		res[alloc] = sign;
	return (res);
}
