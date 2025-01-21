/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimpa <jimpa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:02:42 by jimpa             #+#    #+#             */
/*   Updated: 2025/01/20 18:54:36 by jimpa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

/* off lib */
# include <stdio.h>
# include <stdint.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>

int		ft_tolower(int c);
size_t	ft_strlen(const char *str);
void	ft_putchar(char c);
void	ft_putstr(char *str);
char	*ft_itoa_base(int n, int base);
char	*ft_itoa_base_printf(unsigned long value, int base);
char	*ft_itoa(int n);
char	*ft_unitoa(unsigned int n);

#endif
