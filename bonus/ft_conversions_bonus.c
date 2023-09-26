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
#include <stdio.h>

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

static int is_conversion(char const c)
{
	if (c == 'c' || c == 's' || c == 'u' || c == 'p' || c == 'i' || c == 'd' 
		|| c == 'x' || c == 'X' || c == '%')
		return (1);
	return (0);
}

static int	is_flag(char const c)
{
	if (c == '.' || c == '#' || c == ' ' || c == '+' || c == '-' || c == '0')
		return (1);
	return (0);
}

static char get_flag(const char *str)
{
	if (!is_flag(*str) && !ft_isdigit(*str))
		return (-1);
	return (*str);
}

static char	get_conversion(const char *str)
{
	while (*str != '\0' && !is_conversion(*str))
		str++;
	if (is_conversion(*str))
		return ((char)*str);
	return (-1);
}

static int	get_num(const char *str, char flag)
{
	if (is_flag(flag))
		str++;
	return (ft_atoi(str));
}

static t_list	*truncate_lst(t_list *lst, int num)
{
	t_list	*node;
	int 	count;

	count = 0;
	node = lst;
	while (count < num && lst->next != NULL)
	{
		lst = lst->next;
		count++;
	}
	if (count == num)
		ft_lstclear(&lst, del_node);
	return (node);
}

static t_list	*create_char_lst(int num, char c)
{
	int 	count;
	int		err;
	t_list	*lst;
	t_list	*node;

	lst = NULL;
	err = 0;
	count = 0;
	while (count < num)
	{
		node = create_lst(c, &lst, &err);
		if (node == NULL)
			return (NULL);
		count++;
		ft_lstadd_back(&lst, node);
	}
	return (lst);
}

static t_list	*add_info_to_node(t_list *node, int num, int left, char c)
{
	int		len;
	t_list	*info;

	len = ft_lstsize(node);
	if (num > len)
	{
		info = create_char_lst(num - len, c);
		if (info == NULL)
		{
			ft_lstclear(&node, del_node);
			return (NULL);
		}
		if (left)
		{
			ft_lstadd_back(&info, node);
			return (info);
		}
		ft_lstadd_back(&node, info);
		return (node);
	}
	return (node);
}

static t_list	*redo_node(char c, char flag, int num, t_list *node)
{
	if (flag == '.' && c == 's')
		node = truncate_lst(node, num);
	else if ((flag == '.' || flag == '0') && (c == 'u' || c == 'i' || c == 'd'
		|| c == 'x' || c == 'X'))
		node = add_info_to_node(node, num, 1, '0');
	else if (flag == '-' && c != '%')
		node = add_info_to_node(node, num, 0, ' ');
	else if (ft_isdigit(flag) && c != '%')
		node = add_info_to_node(node, num, 1, ' ');
	//else if (flag == '+' && (c == 'i' || c == 'd'))
		//cosas
	else if (flag == ' ' && (c == 'i' || c == 'd'))
		node = add_info_to_node(node, num, 1, ' ');
	//else if ((flag == '#') && (c == 'x' || c == 'X'))
		//cosas
	else
		node = NULL;
	return (node);
}

t_list	*store_conversion(char const str, t_list **lst, int *err, va_list va)
{
	t_list	*node;

	if (str == 'c')
		node = create_lst(va_arg(va, int), NULL, err);
	else if (str == 's')
		node = str_to_lst(va_arg(va, char *), err);
	else if (str == 'u')
		node = putnbr_uns_err((va_arg(va, unsigned int)), DECBASE, err);
	else if (str == 'p')
		node = ft_putptr(va_arg(va, void *), HEXBASEL, err);
	else if (str == 'i' || str == 'd')
		node = putnbr_sig_err(va_arg(va, int), DECBASE, err);
	else if (str == 'x')
		node = putnbr_uns_err((va_arg(va, unsigned int)), HEXBASEL, err);
	else if (str == 'X')
		node = putnbr_uns_err((va_arg(va, unsigned int)), HEXBASEH, err);
	else if (str == '%')
		node = create_lst('%', NULL, err);
	else
		*err = -1;
	if (!*err)
		return (node);
	else
		ft_lstclear(lst, del_node);
	return (NULL);
}

void	manage_percent(char const *str, t_list **main_lst, int *err, va_list va)
{
	char	flag;
	int		num;
	char	c;
	t_list	*node;

	flag = get_flag(str);
	num = get_num(str, flag);
	c = get_conversion(str);
	node = store_conversion(*str, main_lst, err, va);
	if (!*err && flag != -1)
	{
		if (node == NULL)
			return ;
		node = redo_node(c, flag, num, node);
		if (node == NULL)
		{
			*err = 1;
			ft_lstclear(main_lst, del_node);
			return ;
		}
	}
	ft_lstadd_back(main_lst, node);
}
