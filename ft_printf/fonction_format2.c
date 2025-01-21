/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction_format2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimpa <jimpa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 18:09:27 by jimpa             #+#    #+#             */
/*   Updated: 2024/10/25 12:56:14 by jimpa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	for_exa_up(va_list *args)
{
	char	*result;
	int		nb;
	int		len;

	nb = va_arg(*args, int);
	result = ft_itoa_base(nb, 16);
	len = ft_strlen(result);
	ft_putstr(result);
	free(result);
	return (len);
}

int	for_exa(va_list *args)
{
	int		nb;
	int		i;
	char	*str;

	i = 0;
	nb = va_arg(*args, int);
	str = ft_itoa_base(nb, 16);
	while (str[i])
	{
		str[i] = (char)ft_tolower(str[i]);
		i++;
	}
	ft_putstr(str);
	free(str);
	return (i);
}

int	for_pointer(va_list *args)
{
	int		len;
	int		i;
	void	*ptr;
	char	*result;

	ptr = va_arg(*args, void *);
	if (!ptr)
	{
		ft_putstr("0x0");
		return (3);
	}
	ft_putstr("0x");
	result = ft_itoa_base_printf((unsigned long)ptr, 16);
	if (!result)
		return (0);
	i = 0;
	len = ft_strlen(result) + 2;
	while (result[i])
	{
		result[i] = ft_tolower(result[i]);
		i++;
	}
	ft_putstr(result);
	free(result);
	return (len);
}
