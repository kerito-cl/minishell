/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:08:48 by mquero            #+#    #+#             */
/*   Updated: 2024/11/08 12:11:29 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *str);
int		ft_putnbr_fd(int64_t n, int fd, int count);
int		ft_printhex(uint64_t p, char x, int count);
int		ft_printf(const char *str, ...);

#endif
