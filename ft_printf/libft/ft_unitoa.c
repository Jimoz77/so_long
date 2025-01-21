/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unitoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimpa <jimpa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 13:53:20 by jimpa             #+#    #+#             */
/*   Updated: 2024/10/25 13:54:04 by jimpa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	nb_num(unsigned int n)
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

char	*ft_unitoa(unsigned int n)
{
	unsigned int	num;
	char			*str;
	size_t			nbchiffres;

	num = n;
	nbchiffres = nb_num(n);
	str = (char *)malloc(sizeof(char) * nbchiffres + 1);
	if (!str)
		return (NULL);
	*(str + nbchiffres) = 0;
	while (nbchiffres--)
	{
		*(str + nbchiffres) = num % 10 + '0';
		num = num / 10;
	}
	return (str);
}
