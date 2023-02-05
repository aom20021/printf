/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anollero <anollero@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 16:03:35 by anollero          #+#    #+#             */
/*   Updated: 2023/02/05 13:54:16 by anollero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>
# include "libft.h"

char	*ft_utoa_aux(void);
void	ft_sign_ualloc(unsigned int *aux, char *sign, int *alloc);
char	*ft_utoa(unsigned int n);
int		ft_printf(const char *format, ...);
int		ft_sizehex(unsigned long long num);
char	*ft_atoh(unsigned long long num, int mode);

#endif