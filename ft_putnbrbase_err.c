/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrbase_err.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:25:21 by mpovill-          #+#    #+#             */
/*   Updated: 2023/09/18 15:25:28 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	put_nbr_long(unsigned long num, char *base, int *err, int len)
{
	int	count;

	if (num / len < 1)
		return (ft_putchar_err(base[num], err));
	else
	{
		count = put_nbr_long(num / len, base, err, len);
		if (!*err)
			count += ft_putchar_err(base[(num % len)], err);
		return (count);
	}
}

int	ft_longputnbr_base_err(unsigned long nbr, char *base, int *err, int len)
{
	return (put_nbr_long(nbr, base, err, len));
}

static int	put_nbr_int(unsigned int num, char *base, int *err, int len)
{
	int	count;

	if (num / len < 1)
		return (ft_putchar_err(base[num], err));
	else
	{
		count = put_nbr_int(num / len, base, err, len);
		if (!*err)
			count += ft_putchar_err(base[(num % len)], err);
		return (count);
	}
}

int	ft_unsputnbr_base_err(unsigned int nbr, char *base, int *err, int len)
{
	return (put_nbr_int(nbr, base, err, len));
}

int	ft_putnbr_base_err(int nbr, char *base, int *err, int len)
{
	unsigned int	num;
	int				count;

	count = 0;
	if (nbr < 0)
	{
		count += ft_putchar_err('-', err);
		num = nbr * -1;
	}
	else
		num = nbr;
	if (!*err)
		return (put_nbr_int(num, base, err, len) + count);
	return (count);
}
