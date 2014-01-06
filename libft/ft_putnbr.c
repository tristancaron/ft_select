/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 10:20:46 by tcaron            #+#    #+#             */
/*   Updated: 2013/11/21 10:20:47 by tcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_pow(int nb, int exponent);

void		ft_putnbr(int n)
{
	int		save;
	size_t	len;

	save = n;
	len = 0;
	if (!n)
		ft_putchar('0');
	if (n < 0)
	{
		ft_putchar('-');
		n = -n;
	}
	while (save)
	{
		save /= 10;
		len++;
	}
	while (len)
	{
		ft_putchar(n / ft_pow(10, (int)len - 1) + '0');
		n -= n / ft_pow(10, (int)len - 1) * ft_pow(10, (int)len - 1);
		len--;
	}
}

static int	ft_pow(int nb, int exponent)
{
	if (!exponent)
		return (1);
	return (nb * ft_pow(nb, exponent - 1));
}
