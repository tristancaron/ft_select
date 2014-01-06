/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 10:21:54 by tcaron            #+#    #+#             */
/*   Updated: 2013/11/21 10:21:54 by tcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_pow(int nb, int exponent);

void		ft_putnbr_fd(int n, int fd)
{
	int		save;
	size_t	len;

	save = n;
	len = 0;
	if (!n)
		ft_putchar_fd('0', fd);
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = -n;
	}
	while (save)
	{
		save /= 10;
		len++;
	}
	while (len)
	{
		ft_putchar_fd(n / ft_pow(10, (int)len - 1) + '0', fd);
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
