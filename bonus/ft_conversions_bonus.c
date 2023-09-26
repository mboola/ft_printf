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
	if (!is_flag(*str) && !ft_is_digit(*str))
		return (-1);
	return (*str);
}

static char	get_conversion(const char *str)
{
	char	flag;
	while (*str != '\0' && !is_conversion(*str))
		str++;
	if (is_conversion(*str))
		return ((char)*str);
	return (-1);
}

static int	get_num(const char *str, char flag)
{
	int	num;

	if (is_flag(flag))
		str++;
	num = ft_atoi(str);
	if (num < 1)
		return(-1);
	return (num);
}

static t_list	redo_node(char c, char flag, int num, t_list lst)
{
	t_list	*node;

	if (flag == '.' && c == 's')
		//cosas
	else if ((flag == '.' || flag == '0') && (c == 'u' || c == 'i' || c == 'd'
		|| c == 'x' || c == 'X'))
		//cosas
	else if (flag == '-' && c != '%')
		//cosas
	else if (ft_isdigit(flag) && c != '%')
		//cosas
	else if (flag == '+' && (c == 'i' || c == 'd'))
		//cosas
	else if (flag == ' ' && (c == 'i' || c == 'd'))
		//cosas
	else if ((flag == '#') && (c == 'x' || c == 'X'))
		//cosas
	else
		node = NULL;
	return (node);
}

void	manage_percent(char const *str, t_list **lst, int *err, va_list va)
{
	char	flag;
	int		num;
	char	c;
	t_list	*node;

	flag = get_flag(str);
	num = get_num(str, flag);
	c = get_conversion(str);
	node = store_conversion(str, lst, err, va);
	if (!*err)
	{
		if (node == NULL)
			return ;
		node = redo_node(c, flag, num, node);
		if (node == NULL)
		{

		}
	}
}

t_list	store_conversion(char const str, t_list **lst, int *err, va_list va)
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
		return (node);
	else
		ft_lstclear(lst, del_node);
	return (NULL);
}
