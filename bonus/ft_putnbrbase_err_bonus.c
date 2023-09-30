/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrbase_err_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:28:42 by mpovill-          #+#    #+#             */
/*   Updated: 2023/09/26 11:28:43 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static int	rec_putnbr(char *str, unsigned int number, int pos, char *base)
{
	if (number / ft_strlen(base) < 1)
		*str = base[number];
	else
	{
		pos = rec_putnbr(str, number / ft_strlen(base), pos, base);
		*(str + pos) = base[number % ft_strlen(base)];
	}
	return (pos + 1);
}

static int	get_numsize(int n, int len)
{
	int				size;
	unsigned int	num;

	size = 1;
	if (n < 0)
	{
		num = n * -1;
		size++;
	}
	else if (n == 0)
	{
		num = n;
		size++;
	}
	else
		num = n;
	while (num > 0)
	{
		num /= len;
		size++;
	}
	return (size);
}

/* Creates a t_lst with the unsigned int recived from param
*/
char	*putnbr_uns_err(unsigned int nbr, char *base, int *err)
{
	char			*str;
	int				size;
	unsigned int	num;

	size = 1;
	if (nbr == 0)
		size++;
	num = nbr;
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
	rec_putnbr(str, nbr, 0, base);
	*(str + size - 1) = '\0';
	return (str);
}

char	*putnbr_sig_err(int nbr, char *base, int *err)
{
	char	*str;
	int		size;

	size = get_numsize(nbr, ft_strlen(base));
	str = malloc(sizeof(char) * size);
	if (str == NULL)
	{
		*err = 1;
		return (NULL);
	}
	if (nbr < 0)
	{
		*str = '-';
		rec_putnbr(str + 1, nbr * -1, 0, base);
	}
	else
		rec_putnbr(str, nbr, 0, base);
	*(str + size - 1) = '\0';
	return (str);
}
