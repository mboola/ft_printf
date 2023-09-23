/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 12:11:32 by mpovill-          #+#    #+#             */
/*   Updated: 2023/09/14 12:20:50 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	del_node(void *content)
{
	free(content);
}

t_list	*create_node(char c, t_list **lst, int *err)
{
	char	*ptr;
	t_list	*node;

	ptr = malloc(sizeof(char));
	if (ptr == NULL)
	{
		*err = 1;
		ft_lstclear(lst, del_node);
		return (NULL);
	}
	*ptr = c;
	node = ft_lstnew(ptr);
	if (node == NULL)
	{
		*err = 1;
		ft_lstclear(lst, del_node);
		del_node(ptr);
		return (NULL);
	}
	return (node);
}

static t_list	*ft_mapstr(char const *str, va_list va, int *err)
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
			node = create_node(*str, &lst, err);
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
	lst = ft_mapstr(str, va, &err);
	va_end(va);
	if (err)
		return (-1);
	ft_putstr_lst(lst, &err);
	if (err)
		return (-1);
	err = ft_lstsize(lst);
	ft_lstclear(&lst, del_node);
	return (err);
}
