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

static void	put_nbr(unsigned int num, char *base, int *err, int len)
{
	if (num / len < 1)
		ft_putchar_err(base[num], err);
	else
	{
		put_nbr(num / len, base, err, len);
		if (!*err)
			ft_putchar_err(base[(num % len)], err);
	}
}

void	ft_unsputnbr_base_err(unsigned int nbr, char *base, int *err, int len)
{
	put_nbr(nbr, base, err, len);
}

void	ft_putnbr_base_err(int nbr, char *base, int *err, int len)
{
	unsigned int	num;

	if (nbr < 0)
	{
		ft_putchar_err('-', err);
		num = nbr * -1;
	}
	else
		num = nbr;
	if (!*err)
		put_nbr(num, base, err, len);
}