/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:27:57 by mpovill-          #+#    #+#             */
/*   Updated: 2023/09/26 11:27:58 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static int	rec_putnbr_b(char *str, unsigned int number, int pos, char *base)
{
	if (number / ft_strlen(base) < 1)
		*str = base[number];
	else
	{
		pos = rec_putnbr_b(str, number / ft_strlen(base), pos, base);
		*(str + pos) = base[number % ft_strlen(base)];
	}
	return (pos + 1);
}

static int	rec_putnbr_b_l(char *str, unsigned long number, int pos, char *base)
{
	if (number / ft_strlen(base) < 1)
		*str = base[number];
	else
	{
		pos = rec_putnbr_b_l(str, number / ft_strlen(base), pos, base);
		*(str + pos) = base[number % ft_strlen(base)];
	}
	return (pos + 1);
}

char	*ft_itoa_base_long(unsigned long n, char *base, int *err)
{
	int				size;
	unsigned long	num;
	char			*str;

	size = 1;
	if (n == 0)
		size++;
	num = n;
	while (num > 0)
	{
		num /= ft_strlen(base);
		size++;
	}
	str = malloc(sizeof(char) * size);
	if (str == NULL)
	{
		*err = 1;
		return (NULL);
	}
	rec_putnbr_b_l(str, n, 0, base);
	*(str + size - 1) = '\0';
	return (str);
}

char	*ft_itoa_base(unsigned int n, char *base, char *str, int size)
{
	rec_putnbr_b(str, n, 0, base);
	*(str + size - 1) = '\0';
	return (str);
}
