/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalhi <<marvin@42.fr>>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 16:31:47 by nsalhi            #+#    #+#             */
/*   Updated: 2023/02/20 17:26:46 by nassimsalhi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include <stddef.h>

int		ft_printf(const char *str, ...);
void	ft_putchar_len(char c, int *len);
void	ft_putnbr_len(int n, int *len);
void	ft_put_str_len(char *str, int *len);
void	ft_put_base_len(unsigned int nbr, const char *base, int *lenght);
void	ft_put_base_long_len(long nbr, const char *base, int *length);
void	ft_putvoid(void *ptr, int *len);
void	ft_put_hex_lowercase_len(unsigned int c, int *len);
void	ft_put_hex_uppercase_len(unsigned int c, int *len);
void	ft_put_nbr_unsigned_len(unsigned int c, int *len);
void	ft_unsigned_len(unsigned int c, int *len);
size_t	ft_strlen(const char *str);

#endif
