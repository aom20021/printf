/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anollero <anollero@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 16:00:46 by anollero          #+#    #+#             */
/*   Updated: 2023/01/26 13:49:47 by anollero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/ft_printf.h"
#include "include/libft.h"
#include "stdio.h"

int size_unsigned_num_hex(unsigned int num)
{
    int i = 0;
    while (num != 0)
    {
        num = num / 16;
        i++;
        if (num % 10 == 0 && num < 100 && num != 0)
        {
            i++;
        }
    }
    return i;
}

char *atoh(unsigned int num)
{
    char *res = calloc(size_unsigned_num_hex(num), 1);
    int i = size_unsigned_num_hex(num);
    char hex[16] = "0123456789ABCDEF";
    while (i != 0)
    {
        res[i - 1] = hex[num % 16];
        num = num / 16;
        i--;
    }
    return res;
}


char	*ft_utoa_aux()
{
	char	*res;

	res = (char *)malloc(2);
	if (res == NULL)
		return (NULL);
	res[0] = 48;
	res[1] = '\0';
	return (res);
}

void	ft_sign_ualloc(unsigned int *aux, unsigned int *n, char *sign, int *alloc)
{
	*(alloc) = 1;
	if (*n < 0)
	{
		*(sign) = '-';
		*n = -(*(n));
		*(alloc) = *(alloc) + 1;
	}
	else
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
	ft_sign_ualloc(&aux, &n, &sign, &alloc);
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

void	ft_formatsel(char format, int *length, va_list pa)
{
	char carac;
	char *string;

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
		ft_putstr_fd(atoh(va_arg(pa, int)), 1);
	}
	else if (format == 'u')
	{
		unsigned int aux = va_arg(pa, unsigned int);
		if (aux < 0)
			aux = 4294967286 - aux;
		char *ret2 = ft_utoa(aux);
		(*length) = *length + ft_strlen(ret2);
		free(ret2);
		ft_putnbr_fd(aux, 1);
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
