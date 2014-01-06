/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 10:05:42 by tcaron            #+#    #+#             */
/*   Updated: 2013/11/21 10:05:42 by tcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int		ft_init_itoa(int n, char **result);
static int		ft_pow(int nb, int exponent);

char			*ft_itoa(int n)
{
	char	*result;
	int		len;
	char	*save;

	result = (char *)malloc(sizeof(char));
	result = "0";
	if (!n)
		return (result);
	len = ft_init_itoa(n, &result);
	save = result;
	if (*result == '-')
	{
		result++;
		n = -n;
	}
	while (len)
	{
		*result = n / ft_pow(10, len - 1) + '0';
		n -= n / ft_pow(10, len - 1) * ft_pow(10, len - 1);
		result++;
		len--;
	}
	*result = '\0';
	return (save);
}

static int		ft_init_itoa(int n, char **result)
{
	int		len;
	int		negative;

	len = 0;
	negative = 0;
	if (n < 0)
	{
		negative = 1;
		len++;
	}
	while (n)
	{
		n /= 10;
		len++;
	}
	(*result) = (char *)malloc((len + 1)* sizeof(char));
	if (negative)
	{
		**result = '-';
		len--;
	}
	return (len);
}

static int		ft_pow(int nb, int exponent)
{
	if (!exponent)
		return (1);
	return (nb * ft_pow(nb, exponent - 1));
}
