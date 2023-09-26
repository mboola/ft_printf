/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:28:22 by mpovill-          #+#    #+#             */
/*   Updated: 2023/09/26 11:28:23 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static t_list	*ft_create_final_lst(char const *str, va_list va, int *err)
{
	t_list	*lst;
	t_list	*node;

	lst = NULL;
	while (*str != '\0' && !*err)
	{
		if (*str == '%')
		{
			str++;
			choose_conversion(str, &lst, err, va);
		}
		else
		{
			node = create_lst(*str, &lst, err);
			if (node == NULL)
				return (NULL);
			ft_lstadd_back(&lst, node);
		}
		str++;
	}
	return (lst);
}

int	ft_printf(char const *str, ...)
{
	int		err;
	va_list	va;
	t_list	*lst;

	if (str == NULL)
		return (-1);
	err = 0;
	va_start(va, str);
	lst = ft_create_final_lst(str, va, &err);
	va_end(va);
	if (err)
		return (-1);
	print_lst(lst, &err);
	if (err)
	{
		ft_lstclear(&lst, del_node);
		return (-1);
	}
	err = ft_lstsize(lst);
	ft_lstclear(&lst, del_node);
	return (err);
}
