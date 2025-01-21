/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimpa <jimpa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:21:20 by jimi              #+#    #+#             */
/*   Updated: 2024/10/25 13:02:00 by jimpa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// toutes les fonctions qui servent a imprimer tout les formats "%..."

void	for_char(va_list *args)
{
	char	c;

	c = va_arg(*args, int);
	ft_putchar(c);
}

int	for_str(va_list *args)
{
	char	*str;
	int		len;

	str = va_arg(*args, char *);
	if (str == NULL)
		str = "(null)";
	ft_putstr(str);
	len = ft_strlen(str);
	return (len);
}

int	for_deci_int(va_list *args)
{
	char	*result;
	int		nb;
	int		len;

	nb = va_arg(*args, int);
	result = (ft_itoa (nb));
	len = ft_strlen(result);
	ft_putstr(result);
	free(result);
	return (len);
}

int	for_un_int(va_list *args)
{
	unsigned int	nb;
	int				len;
	char			*result;

	nb = va_arg(*args, unsigned int);
	result = ft_unitoa(nb);
	len = ft_strlen(result);
	ft_putstr(result);
	free(result);
	return (len);
}

void	for_prcent(void)
{
	ft_putchar('%');
}
