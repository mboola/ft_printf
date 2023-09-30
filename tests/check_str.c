#include <stdio.h>
#include <stdlib.h>

typedef struct t_percent
{
    char    *info;
	char    flag;
    char    conversion;
    int     precision;
    int     spaces;
    int     zeros;
}	t_percent;

static int is_conversion(char c)
{
	if (c == 'c' || c == 's' || c == 'u' || c == 'p' || c == 'i' || c == 'd' 
		|| c == 'x' || c == 'X' || c == '%')
		return (1);
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	count;

	count = 0;
	while (*(s + count) != '\0')
		count++;
	return (count);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	size;

	size = ft_strlen(src);
	if (dstsize == 0)
		return (size);
	i = 0;
	while (*(src + i) != '\0' && i < dstsize - 1)
	{
		*(dst + i) = *(src + i);
		i++;
	}
	*(dst + i) = '\0';
	return (size);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	s_len;
	size_t	size;

	if (s == NULL)
		size = 1;
	else
	{
		s_len = ft_strlen(s);
		if (start > s_len)
			size = 1;
		else if (len > s_len - start)
			size = s_len - start + 1;
		else
			size = len + 1;
	}
	str = malloc(sizeof(char) * size);
	if (str == NULL)
		return (NULL);
	if (start > s_len)
		*str = '\0';
	else
		ft_strlcpy(str, s + start, size);
	return (str);
}

static char	*get_substr_conversion(char *str, int *err)
{
	int		count;
	char	*substr;

	count = 0;
	while (*(str + count) != '\0' && !is_conversion(*(str + count)))
		count++;
	if (*(str + count) == '\0')
	{
		*err = 1;
		return (NULL);
	}
	substr = ft_substr(str, 0, count + 1);
	if (substr == NULL)
		*err = 1;
	return (substr);
}

static void	del_t_percent(t_percent *options)
{
	if (options->info != NULL)
		free(options->info);
	free(options);
}

static char	get_conversion(char *str)
{
	if (*str == '%')
		return (*str);
	while (*str != '\0' && !is_conversion(*str))
		str++;
	if (*str == '\0')
		return (0);
	if (*str == '%')
		return (0);
	return (*str);
}

int	ft_atoi(const char *str)
{
	int				num;
	int				n;

	while (*str == '\f' || *str == '\n' || *str == '\r'
		|| *str == '\t' || *str == '\v' || *str == ' ')
		str++;
	n = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			n *= -1;
		str++;
	}
	while (*str == '0')
		str++;
	num = 0;
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10 + (*str - '0');
		str++;
	}
	num *= n;
	return (num);
}

static int	get_precision(char *str, char conv)
{
	int	count;

	count = 0;
	while (*str != '\0')
	{
		if (*str == '.')
			count++;
		str++;
	}
	if (count > 1)
		return (-1);
	if (count)
	{
		if (conv == 'p')
			return (-1);
		else if (conv == 'c')
			return (-1);
	}
	return (count);
}

static int	is_flag(char c)
{
	if (c == '.' || c == '#' || c == ' ' || c == '+' || c == '-' || c == '0')
		return (1);
	return (0);
}

static char get_flag(char *str, char conv)
{
	char	flag;

	if (!is_flag(*str) && !ft_isdigit(*str) && *str != conv && *str != '*')
		return (0);
	flag = *str;
	if (flag == '#' && !(conv == 'x' || conv == 'X'))
		return (0);
	if ((flag == '+' || flag == ' ') && !(conv == 'i' || conv == 'd'))
		return (0);
	if (flag == '0' && (conv == 's' || conv == 'c' || conv == 'p'))
		return (0);
	if (is_flag(flag))
		return (*str);
	return (-1);
}

static int	check_num_correct(char *str, char c, int *ptr)
{
	int		i;
	char	*tmp;

	i = 0;
	if (*str == '*' && *(str + 1) != c)
		return (0);
	else if (*str == '*')
	{
		*ptr = 10;
		return (1);
	}
	else if (*str == '0')
		return (0);
	while (ft_isdigit(*(str + i)))
		i++;
	if (*(str + i) != c)
		return (0);
	tmp = ft_substr(str, 0, i);
	if (tmp == NULL)
		return (0);
	*ptr = ft_atoi(tmp);
	free(tmp);
	return (i);
}

static int	check_nums(t_percent *options)
{
	char	*str;
	int		i;

	str = options->info;
	//if (options->flag == '0' && *(str + 1) == '0')
	//	return (0);
	if (options->flag != -1)
		str++;
	if (options->precision)
	{
		i = check_num_correct(str, '.', &(options->spaces));
		if (!i)
			return (0);
		str += i + 1;
	}
	else
		options->spaces = 0;
	if (!check_num_correct(str, options->conversion, &(options->zeros)))
		return (0);
	return (1);
}

/*	Flag might not exist and precision might also not exist
*/
static int	check_options_correct(t_percent *options)
{
	if (options->info == NULL)
		return (0);
	options->conversion = get_conversion(options->info);
	if (!options->conversion)
		return (0);
	options->precision = get_precision(options->info, options->conversion);
	if (options->precision == -1)
		return (0);
	options->flag = get_flag(options->info, options->conversion);
	if (!options->flag)
		return (0);
	return (check_nums(options));
}

static char	*create_output(t_percent *options)
{
	//pillo resultat, foto zeros i foto espai
}

static char	*get_final_output(t_percent *options, int *err)
{
	char	output;

	if (!check_options_correct(options))
	{
		*err = 1;
		return (NULL);
	}
	//output = create_output(options);
	//if (output == NULL)
	//	*err = 1;
	return (NULL);
}

void	print_options(t_percent *options)
{
	printf("Info: %s\n", options->info);
	printf("Flag: %c\n", options->flag);
	printf("Conv: %c\n", options->conversion);
	printf("Prec: %d\n", options->precision);
	printf("Spac: %d\n", options->spaces);
	printf("Zero: %d", options->zeros);
}

void	test_correct(char *str, int *err)
{
	t_percent	*options;
	char		*output;

	options = malloc(sizeof(t_percent));
	if (options == NULL)
	{
		*err = 1;
		return ;
	}
	options->info = get_substr_conversion(str, err);
	if (options->info == NULL)
		del_t_percent(options);
	else
	{
		//printf("%s", options->info);
		get_final_output(options, err);
		print_options(options);
		del_t_percent(options);
	}
}

int	main(void)
{
	int	err;

	err = 0;
	test_correct("001.12d", &err);
	if (err)
		printf("Error\n");
	else
		printf("\n");
	return (0);
}
