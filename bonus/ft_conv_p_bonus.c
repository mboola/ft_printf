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

static char	*add_0x_front(char **str, int *err)
{
	char	*front;

	front = ft_strdup("0x");
	if (front == NULL)
	{
		*err = -1;
		return (NULL);
	}
	return (join_and_free(&front, str, err));
}

static int	rec_putnbr(char *str, unsigned long number, int pos, char *base)
{
	if (number / ft_strlen(base) < 1)
		*str = base[number];
	else
	{
		pos = rec_putnbr(str, number / ft_strlen(base), pos, base);
		*(str + pos) = base[number % ft_strlen(base)];
	}
	return (pos + 1);
}

static char	*ft_itoa_base_addr(unsigned long n, char *base, int *err)
{
	int				size;
	unsigned long	num;
	char			*str;

	size = 1;
	if (n == 0)
		size++;
	num = n;
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
	rec_putnbr(str, n, 0, base);
	*(str + size - 1) = '\0';
	return (str);
}

static char	*ft_putptr(void *ptr, char *base, int *err)
{
	char	*str;

	str = ft_itoa_base_addr((unsigned long)ptr, base, err);
	if (str == NULL)
		return (NULL);
	return (add_0x_front(&str, err));
}

char	*create_output_pointer(void *ptr, t_percent *opt, int *err)
{
	char	*output;
	char	*spaces;

	/*if (ptr == NULL && *(opt->info) != opt->conv)
		output = copy_str("(nil)", err);
	else*/
	output = ft_putptr(ptr, HEXBASEL, err);
	spaces = create_str(opt->num_spaces - ft_strlen(output), ' ', err);
	if (*err == -1)
	{
		free(output);
		return (NULL);
	}
	if (opt->sp_inv)
		output = join_and_free(&output, &spaces, err);
	else
		output = join_and_free(&spaces, &output, err);
	return (output);
}
