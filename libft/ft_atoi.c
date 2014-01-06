/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 09:58:51 by tcaron            #+#    #+#             */
/*   Updated: 2013/11/21 14:14:31 by tcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static unsigned int		ft_uatoi(const char *nbr);

int						ft_atoi(const char *str)
{
	int		negative;

	negative = 1;
	if (!str || ((*str < 47 || *str > 58) && *str != '-' && *str != ' '
		&& *str != '\n' && *str != '\v' && *str != '\t' && *str != '\r'
		&& *str != '\f' && *str != '+'))
		return (0);
	while (*str == ' ' || *str == '\n' || *str == '\v' || *str == '\t'
		|| *str == '\r' || *str == '\f' || *str == '+')
		str++;
	if (*str == '-')
	{
		negative = -1;
		str++;
	}
	if (!str || ((*str < 47 || *str > 58) && *str != '-' && *str != ' '))
		return (0);
	return (ft_uatoi(str) * negative);
}

static unsigned int		ft_uatoi(const char *nbr)
{
	unsigned int	res;

	res = 0;
	while (*nbr)
	{
		if (*nbr < 47 || *nbr > 58)
			break ;
		res = *nbr - '0' + res * 10;
		nbr++;
	}
	return (res);
}
