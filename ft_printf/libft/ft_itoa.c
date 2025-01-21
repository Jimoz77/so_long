/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiparcer <jiparcer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 11:52:21 by jiparcer          #+#    #+#             */
/*   Updated: 2024/10/14 12:37:45 by jiparcer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	nb_num(int n)
{
	size_t	i;

	i = 1;
	while (n / 10 != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	long int	num;
	char		*str;
	size_t		nbchiffres;

	num = n;
	nbchiffres = nb_num(n);
	if (n < 0)
	{
		num *= -1;
		nbchiffres++;
	}
	str = (char *)malloc(sizeof(char) * nbchiffres + 1);
	if (!str)
		return (NULL);
	*(str + nbchiffres) = 0;
	while (nbchiffres--)
	{
		*(str + nbchiffres) = num % 10 + '0';
		num = num / 10;
	}
	if (n < 0)
		*(str + 0) = '-';
	return (str);
}
