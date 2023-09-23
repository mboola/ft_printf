/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 02:39:50 by mpovill-          #+#    #+#             */
/*   Updated: 2023/09/23 02:39:51 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	store_n_rec(char *str, unsigned long number, int pos, char *base)
{
	if (number / ft_strlen(base) < 1)
		*str = base[number];
	else
	{
		pos = store_n_rec(str, number / ft_strlen(base), pos, base);
		*(str + pos) = base[number % ft_strlen(base)];
	}
	return (pos + 1);
}

char	*ft_itoa_base_unsigned(unsigned long n, char *base)
{
	char			*str;
	size_t			size;
	size_t			len;
	unsigned long	num;

	size = 1;
	if (n == 0)
		size++;
	num = n;
	len = ft_strlen(base);
	while (num > 0)
	{
		num /= len;
		size++;
	}
	str = malloc(sizeof(char) * size);
	if (str == NULL)
		return (NULL);
	store_n_rec(str, n, 0, base);
	*(str + size - 1) = '\0';
	return (str);
}

static int	get_num_len(int n, int len)
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

char	*ft_itoa_base_signed(int n, char *base)
{
	char			*str;
	int				size;
	unsigned int	number;

	size = get_num_len(n, ft_strlen(base));
	str = malloc(sizeof(char) * size);
	if (str == NULL)
		return (NULL);
	if (n < 0)
	{
		*str = '-';
		number = n * -1;
		store_n_rec(str + 1, number, 0, base);
	}
	else
		store_n_rec(str, n, 0, base);
	*(str + size - 1) = '\0';
	return (str);
}