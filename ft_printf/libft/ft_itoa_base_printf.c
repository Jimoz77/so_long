/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_printf.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimpa <jimpa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:49:57 by jimpa             #+#    #+#             */
/*   Updated: 2024/10/25 13:06:50 by jimpa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_num_length(unsigned long value, int base)
{
	int	length;

	length = 0;
	if (value == 0)
		return (1);
	while (value > 0)
	{
		value /= base;
		length++;
	}
	return (length);
}

char	*ft_itoa_base_printf(unsigned long value, int base)
{
	char			*str;
	char			*base_digits;
	int				length;
	unsigned long	temp_value;

	base_digits = "0123456789abcdef";
	if (base < 2 || base > 16)
		return (NULL);
	length = get_num_length(value, base);
	str = (char *)malloc(length + 1);
	if (!str)
		return (NULL);
	str[length] = '\0';
	while (length > 0)
	{
		str[--length] = base_digits[value % base];
		value /= base;
	}
	return (str);
}
