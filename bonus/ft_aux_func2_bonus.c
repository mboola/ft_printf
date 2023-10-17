/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aux_func2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:27:46 by mpovill-          #+#    #+#             */
/*   Updated: 2023/09/26 11:27:47 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

void	ft_putchar_err(char c, int *len, int *err)
{
	if (write(1, &c, 1) < 0)
		*err = -1;
	else
		*len = *len + 1;
}

static void	ft_putstr_err(char	*str, int *len, int *err)
{
	if (str == NULL)
		*err = -1;
	else
	{
		while (*err != -1 && *str != '\0')
		{
			ft_putchar_err(*str, len, err);
			str++;
		}
	}
}

void	print_and_free_output(char **output, t_percent *opt, int *len, int *err)
{
	if (opt->is_null && opt->sp_inv)
		ft_putchar_err('\0', len, err);
	ft_putstr_err(*output, len, err);
	if (opt->is_null && !(opt->sp_inv))
		ft_putchar_err('\0', len, err);
	free(*output);
}

char	*add_spaces(char **output, t_percent *options, int *err)
{
	char	*spaces;

	spaces = create_str(options->num_spaces - ft_strlen(*output), ' ', err);
	if (*err)
		return (NULL);
	if (*spaces == '\0' && options->front_space && **output != '-')
	{
		free(spaces);
		spaces = char_to_str(' ', err);
		if (*err == -1)
			return (NULL);
		return (join_and_free(&spaces, output, err));
	}
	if (options->sp_inv)
		*output = join_and_free(output, &spaces, err);
	else
		*output = join_and_free(&spaces, output, err);
	return (*output);
}

char	*add_zeros(char **output, t_percent *opt, int sign_counts, int *err)
{
	char	*zeros;
	size_t	num_chars;

	num_chars = ft_strlen(*output) + sign_counts;
	if (opt->zero && !(opt->prec))
		zeros = create_str(opt->num_spaces - num_chars, '0', err);
	else
		zeros = create_str(opt->num_zeros - num_chars, '0', err);
	if (*err == -1)
	{
		free(*output);
		return (NULL);
	}
	*output = join_and_free(&zeros, output, err);
	return (*output);
}

/*
char	*print_output(char **output, int *len, int *err, char *conv)
{
	if (*output == NULL)
	{
		*err = -1;
		return (NULL);
	}
	if (**output == '\0' && *conv == 'c')
		ft_putchar_err(**output, len, err);
	return (print_and_reset(output, len, err, 1));
}
*/
