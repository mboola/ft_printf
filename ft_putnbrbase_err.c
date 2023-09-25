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
t_list	*putnbr_uns_err(unsigned int nbr, char *base, int *err)
{
	char			*str;
	t_list			*lst;
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
	str = ft_itoa_base(nbr, base, str, size);
	lst = str_to_lst(str, err);
	free(str);
	return (lst);
}

/*	Creates a t_list of chars of an int with sign (char included)
*/
t_list	*putnbr_sig_err(int nbr, char *base, int *err)
{
	char	*str;
	t_list	*lst;
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
		ft_itoa_base(nbr * -1, base, str + 1, size - 1);
	}
	else
		str = ft_itoa_base(nbr, base, str, size);
	lst = str_to_lst(str, err);
	free(str);
	return (lst);
}
