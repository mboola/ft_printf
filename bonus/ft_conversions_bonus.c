/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conversions_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:27:34 by mpovill-          #+#    #+#             */
/*   Updated: 2023/09/26 11:27:35 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

/* Creates a t_lst of the direction of the pointer
	first it creates strings and then it converts them
	and add them to t_lst
*/
t_list	*ft_putptr(void *ptr, char *base, int *err)
{
	t_list			*lst;
	char			*str;
	t_list			*node;

	node = str_to_lst("0x", err);
	if (node == NULL)
		return (NULL);
	lst = NULL;
	ft_lstadd_back(&lst, node);
	str = ft_itoa_base_long((unsigned long)ptr, base, err);
	if (str == NULL)
	{
		ft_lstclear(&lst, del_node);
		return (NULL);
	}
	node = str_to_lst(str, err);
	free(str);
	if (node == NULL)
	{
		ft_lstclear(&lst, del_node);
		return (NULL);
	}
	ft_lstadd_back(&lst, node);
	return (lst);
}

void	choose_conversion(char const *str, t_list **lst, int *err, va_list va)
{
	t_list	*node;

	if (*str == 'c')
		node = create_lst(va_arg(va, int), NULL, err);
	else if (*str == 's')
		node = str_to_lst(va_arg(va, char *), err);
	else if (*str == 'u')
		node = putnbr_uns_err((va_arg(va, unsigned int)), DECBASE, err);
	else if (*str == 'p')
		node = ft_putptr(va_arg(va, void *), HEXBASEL, err);
	else if (*str == 'i' || *str == 'd')
		node = putnbr_sig_err(va_arg(va, int), DECBASE, err);
	else if (*str == 'x')
		node = putnbr_uns_err((va_arg(va, unsigned int)), HEXBASEL, err);
	else if (*str == 'X')
		node = putnbr_uns_err((va_arg(va, unsigned int)), HEXBASEH, err);
	else if (*str == '%')
		node = create_lst('%', NULL, err);
	else
		*err = -1;
	if (!*err)
		ft_lstadd_back(lst, node);
	else
		ft_lstclear(lst, del_node);
}

