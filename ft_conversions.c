/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conversions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 12:58:29 by mpovill-          #+#    #+#             */
/*   Updated: 2023/09/14 12:58:30 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 12:58:29 by mpovill-          #+#    #+#             */
/*   Updated: 2023/09/14 12:58:30 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_list	*str_to_lst(char *str, int *err)
{
	t_list	*lst;
	t_list	*node;

	if (str == NULL)
		return (NULL);
	lst = NULL;
	while (*str != '\0')
	{
		node = create_node(*str, &lst, err);
		if (node == NULL)
			return (NULL);
		ft_lstadd_back(&lst, node);
		str++;
	}
	return (lst);
}

t_list	*ft_putptr(void *ptr, int *err)
{
	unsigned long	addr;
	t_list			*lst;
	t_list			*node;

	node = str_to_lst("0x", err);
	if (node == NULL)
		return (NULL);
	lst = NULL;
	ft_lstadd_back(&lst, node);
	addr = (unsigned long)ptr;
	node = putnbr_uns_err(addr, HEXBASEL, err);
	if (node == NULL)
		return (NULL);
	ft_lstadd_back(&lst, node);
	return (lst);
}

void	choose_conversion(char const *str, t_list **lst, int *err, va_list va)
{
	t_list	*node;

	if (*str == 'c')
		node = create_node(va_arg(va, int), lst, err);
	else if (*str == 's')
		node = str_to_lst(va_arg(va, char *), err);
	else if (*str == 'u')
		node = putnbr_uns_err((unsigned long)(va_arg(va, int)), DECBASE, err);
	else if (*str == 'p')
		node = ft_putptr(va_arg(va, void *), err);
	else if (*str == 'i' || *str == 'd')
		node = putnbr_sig_err(va_arg(va, int), DECBASE, err);
	else if (*str == 'x')
		node = putnbr_uns_err((unsigned long)(va_arg(va, int)), HEXBASEL, err);
	else if (*str == 'X')
		node = putnbr_uns_err((unsigned long)(va_arg(va, int)), HEXBASEH, err);
	else if (*str == '%')
		node = create_node('%', NULL, err);
	else
		*err = -1;
	if (!*err && node != NULL)
		ft_lstadd_back(lst, node);
	else
		ft_lstclear(lst, del_node);
}
