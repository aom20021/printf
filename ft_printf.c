/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anollero <anollero@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 16:00:46 by anollero          #+#    #+#             */
/*   Updated: 2023/01/27 10:54:01 by anollero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/ft_printf.h"
#include "include/libft.h"
#include "stdio.h"

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

int	ft_sizehex(unsigned long num)
{
	int size;

	size = 0;
	while (num != 0)
	{
		num = num / 16;
		size++;
		if ((num != 0) && (num % 10 == 0) && (num < 100))
		{
			size = size + 2;
			num = 0;
		}
	}
	return (size);
}

char	*ft_atoh(unsigned long num, int mode)
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

void	ft_formatsel(char format, int *length, va_list pa)
{
	char	carac;
	char	*string;

	if (format == 'c')
	{
		carac = va_arg(pa, int);
		write(1, &carac, 1);
		(*length) = *length + 1;
	}
	else if (format == 'd' || format == 'i')
	{
		int aux = va_arg(pa, int);
		char *ret2 = ft_itoa(aux);
		(*length) = *length + ft_strlen(ret2);
		free(ret2);
		ft_putnbr_fd(aux, 1);
	}
	else if (format == '%')
	{
		write(1, "%%", 1);
		(*length) = *length + 1;
	}
	else if (format == 's')
	{
		string = va_arg(pa, char *);
		if (string != NULL)
		{
			ft_putstr_fd(string, 1);
			(*length) = *length + ft_strlen(string);
		}
		else
		{
			ft_putstr_fd("(null)", 1);
			(*length) = *length + 6;
		}
	}
	else if (format == 'x' || format == 'X')
	{
		char *str;
		if (format == 'x')
			str = ft_atoh(0xabcdef, 0);
		else
			str = ft_atoh(0xabcdef, 1);
		ft_putstr_fd(str, 1);
		(*length) = *length + ft_strlen(str);
		free(str);
	}
	else if (format == 'u')
	{
		unsigned int aux = va_arg(pa, int);
		char *ret2 = ft_utoa(aux);
		(*length) = *length + ft_strlen(ret2);
		ft_putstr_fd(ret2, 1);
		free(ret2);
	}
	else if (format == 'p')
	{
		char *str;
		ft_putstr_fd("0x", 1);
		str = ft_atoh(va_arg(pa, unsigned long), 0);
		ft_putstr_fd(str, 1);
		(*length) = *length + ft_strlen(str) + 2;
		free(str);
	}
}

int	ft_printf(const char *format, ...)
{
	va_list			pa;
	const char		*formataux;
	int				ret;

	ret = 0;
	va_start(pa, format);
	formataux = format;
	while (*formataux)
	{
		if (*formataux == '%')
		{
			formataux++;
			if (*formataux)
				ft_formatsel(*formataux, &ret, pa);
			else
				break ;
			formataux++;
			continue ;
		}
		write(1, formataux, 1);
		ret++;
		formataux++;
	}
	va_end(pa);
	return (ret);
}
