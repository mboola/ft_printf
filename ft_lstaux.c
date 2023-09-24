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

/*	Converts a string to a t_lst.
	If str is null, it converts is to "(null)"
	It calls create node that manages error when
	creating and setting the error to true
    */
t_list	*str_to_lst(char *str, int *err)
{
	t_list	*lst;
	t_list	*node;

	if (str == NULL)
		return (str_to_lst("(null)", err));
	lst = NULL;
	while (*str != '\0')
	{
		node = create_lst(*str, &lst, err);
		if (node == NULL)
			return (NULL);
		ft_lstadd_back(&lst, node);
		str++;
	}
	return (lst);
}

/*  Function used to free the content of the t_list struct
*/
void	del_node(void *content)
{
	free(content);
}

/*  Creates a new node with char c as content. If node cannot
    be created, it clears the lst passed by param and sets error 
    */
t_list	*create_lst(char c, t_list **lst, int *err)
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

static void	ft_putchar_err(char c, int *err)
{
	if (write(1, &c, 1) < 0)
		*err = -1;
}

/*	Prints the content of the list using putchar with error handling
*/
void	print_lst(t_list *lst, int *err)
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
