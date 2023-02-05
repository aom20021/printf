/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anollero <anollero@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 16:00:46 by anollero          #+#    #+#             */
/*   Updated: 2023/02/05 14:23:52 by anollero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/ft_printf.h"

void	ft_formatnumberchar(char format, int *length, va_list pa)
{
	char	formatchar;
	char	*str;

	if (format == 'c')
	{
		formatchar = va_arg(pa, int);
		write(1, &formatchar, 1);
		(*length) = *length + 1;
	}
	else
	{
		str = ft_itoa(va_arg(pa, int));
		(*length) = *length + ft_strlen(str);
		ft_putstr_fd(str, 1);
		free(str);
	}
}

void	ft_fortmatstring(int *length, va_list pa)
{
	char	*str;

	str = va_arg(pa, char *);
	if (str != NULL)
	{
		ft_putstr_fd(str, 1);
		(*length) = *length + ft_strlen(str);
	}
	else
	{
		ft_putstr_fd("(null)", 1);
		(*length) = *length + 6;
	}
}

void	ft_formatusehex(char format, int *length, va_list pa)
{
	char	*str;

	if (format == 'x' || format == 'X')
	{
		if (format == 'x')
			str = ft_atoh(va_arg(pa, unsigned int), 0);
		else
			str = ft_atoh(va_arg(pa, unsigned int), 1);
		ft_putstr_fd(str, 1);
		(*length) = *length + ft_strlen(str);
		free(str);
	}
	else if (format == 'p')
	{
		ft_putstr_fd("0x", 1);
		str = ft_atoh(va_arg(pa, unsigned long long), 0);
		ft_putstr_fd(str, 1);
		(*length) = *length + ft_strlen(str) + 2;
		free(str);
	}
}

void	ft_formatsel(char format, int *length, va_list pa)
{
	char			*str;
	unsigned int	uintaux;

	if (format == 'c' || format == 'd' || format == 'i')
		ft_formatnumberchar(format, length, pa);
	else if (format == '%')
	{
		write(1, "%%", 1);
		(*length) = *length + 1;
	}
	else if (format == 's')
		ft_fortmatstring(length, pa);
	else if (format == 'x' || format == 'X' || format == 'p')
		ft_formatusehex(format, length, pa);
	else if (format == 'u')
	{
		uintaux = va_arg(pa, int);
		str = ft_utoa(uintaux);
		(*length) = *length + ft_strlen(str);
		ft_putstr_fd(str, 1);
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
