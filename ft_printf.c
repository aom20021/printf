/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anollero <anollero@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 16:00:46 by anollero          #+#    #+#             */
/*   Updated: 2023/01/27 14:03:58 by anollero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/ft_printf.h"
#include "include/libft.h"
#include "stdio.h"

/*size_t	ft_strlen(const char *cadena)
{
	int	index;

	index = 0;
	while (cadena[index] != '\0')
		index++;
	return (index);
}

int	ft_toupper(int ch)
{
	if ('a' <= ch && ch <= 'z')
		return (ch - 32);
	return (ch);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	count;

	count = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	if (dstsize == 1)
		dst[0] = 0;
	while (src[count] != '\0' && count < dstsize - 1)
	{
		dst[count] = src[count];
		count++;
	}
	dst[count] = 0;
	return (ft_strlen(src));
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
}

void	ft_exceptions(int n, int fd)
{
	if (n == 0)
		write(fd, "0", 1);
	if (n == -2147483648)
		write(fd, "-2147483648", 11);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	str[12];
	int		count;

	if (n == 0 || n == -2147483648)
		ft_exceptions(n, fd);
	count = 0;
	if (n < 0 && n != -2147483648)
	{
		n = -n;
		write(fd, "-", 1);
	}
	while (n != 0 && n != -2147483648)
	{
		str[count] = (n % 10) + 48;
		count++;
		n = n / 10;
	}
	str[count] = '\0';
	count--;
	while (count >= 0 && n != -2147483648)
	{
		write(fd, &str[count], 1);
		count--;
	}
}

void	*ft_calloc(size_t nitems, size_t size)
{
	void	*res;
	size_t	count;

	if (nitems > 0 && (size > (SIZE_MAX / nitems)))
		return (0);
	count = 0;
	res = malloc(nitems * size);
	if (res == 0)
		return (0);
	while (count < nitems * size)
	{
		((unsigned char *)res)[count] = 0;
		count++;
	}
	return (res);
}

char	*ft_itoa_aux(int n)
{
	char	*res;

	if (n == 0)
	{
		res = (char *)malloc(2);
		if (res == NULL)
			return (NULL);
		res[0] = 48;
		res[1] = '\0';
		return (res);
	}
	else
	{
		res = (char *)malloc(12);
		if (res == NULL)
			return (NULL);
		ft_strlcpy(res, "-2147483648", 12);
		return (res);
	}
}

void	ft_sign_alloc(int *aux, int *n, char *sign, int *alloc)
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

char	*ft_itoa(int n)
{
	char	sign;
	int		alloc;
	int		aux;
	char	*res;

	aux = n;
	if (n == -2147483648 || n == 0)
		return (ft_itoa_aux(n));
	ft_sign_alloc(&aux, &n, &sign, &alloc);
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
}*/

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

int	ft_sizehex(unsigned long long num)
{
	int size;

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
			str = ft_atoh(va_arg(pa, unsigned long long), 0);
		else
			str = ft_atoh(va_arg(pa, unsigned long long), 1);
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
		str = ft_atoh(va_arg(pa, unsigned long long), 0);
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

/*int main(int argc, char const *argv[])
{
	ft_printf("%x", __LONG_MAX__);
	return 0;
}*/
//  387C55F665 == 947672566