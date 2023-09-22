/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printinfo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 19:38:43 by mpovill-          #+#    #+#             */
/*   Updated: 2023/09/22 19:38:44 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putchar_err(char c, int *err)
{
	if (write(1, &c, 1) < 0)
		*err = -1;
}

void	ft_putstr_lst(t_list *lst, int *err)
{
	if (lst == NULL)
		*err = 1;
	else
	{
		while (lst->next != NULL && !*err)
		{
			ft_putchar_err(*(char *)(lst->content), err);
			lst = lst->next;
		}
		if (!*err)
			ft_putchar_err(*(char *)(lst->content), err);
	}
}
