/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimpa <jimpa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 13:51:25 by jimpa             #+#    #+#             */
/*   Updated: 2024/10/25 13:51:54 by jimpa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_length(unsigned int n, int base)
{
	size_t			len;
	unsigned int	temp;

	len = 1;
	temp = n / base;
	while (temp)
	{
		len++;
		temp /= base;
	}
	return (len);
}

static char	*convert_num(unsigned int num, int base, size_t len, char *digits)
{
	char	*str;

	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len--)
	{
		str[len] = digits[num % base];
		num /= base;
	}
	return (str);
}

char	*ft_itoa_base(int n, int base)
{
	unsigned int	num;
	char			*digits;
	size_t			len;
	char			*str;

	digits = "0123456789ABCDEF";
	if (base < 2 || base > 16)
		return (NULL);
	if (n < 0 && base == 16)
		num = (unsigned int)n;
	else
	{
		if (n < 0)
			num = -n;
		else
			num = n;
	}
	len = get_length(num, base);
	str = convert_num(num, base, len, digits);
	if (!str)
		return (NULL);
	if (n < 0 && base == 10)
		str[0] = '-';
	return (str);
}
