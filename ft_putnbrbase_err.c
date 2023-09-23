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

t_list	*putnbr_uns_err(unsigned long nbr, char *base, int *err)
{
	char	*str;
	t_list	*lst;

	str = ft_itoa_base_unsigned(nbr, base);
	if (str == NULL)
	{
		*err = 1;
		return (NULL);
	}
	lst = str_to_lst(str, err);
	if (lst == NULL)
		return (NULL);
	return (lst);
}

t_list	*putnbr_sig_err(int nbr, char *base, int *err)
{
	char	*str;
	t_list	*lst;

	str = ft_itoa_base_signed(nbr, base);
	if (str == NULL)
	{
		*err = 1;
		return (NULL);
	}
	lst = str_to_lst(str, err);
	if (lst == NULL)
		return (NULL);
	return (lst);
}