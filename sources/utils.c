/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:31:37 by pmolzer           #+#    #+#             */
/*   Updated: 2024/08/25 21:58:07 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

// Prints usage instructions for the program
void	print_usage(void)
{
	printf("Error: Invalid arguments\n");
	printf("Julia parameters must be in the format x.x, x.xx, or x.xxx\n");
	printf("Julia set parameters must be between -2.0 and 2.0\n");
	printf("Maldelbrot does not need any parameters\n");
	printf("Usage: [mandelbrot | julia <real value> <imaginary value>]\n");
	printf("Example: ./fractol julia 0.1 -0.7\n");
	printf("\t ./fractol mandelbrot\n");
}

// Compares two strings and returns the
// difference between the first non-matching characters
int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while ((s1[i] != '\0' && s2[i] != '\0') && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

// Skips whitespace and handles sign in a
//string, returning the index after these
static int	skip_space_and_sign(char *str, int *is_neg)
{
	int		i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			*is_neg *= -1;
		i++;
	}
	return (i);
}

// Converts a string to a float, handling both
//integer and decimal parts
double	convert_float(char *str)
{
	int		i;
	double	nb;
	int		is_neg;
	double	div;

	nb = 0;
	div = 0.1;
	is_neg = 1;
	i = skip_space_and_sign(str, &is_neg);
	while (str[i] && str[i] != '.')
	{
		nb = (nb * 10.0) + (str[i] - '0');
		i++;
	}
	if (str[i] == '.')
		i++;
	while (str[i])
	{
		nb = nb + ((str[i] - '0') * div);
		div *= 0.1;
		i++;
	}
	if (str[i] && !ft_isdigit(str[i]))
		return (-42);
	return (nb * is_neg);
}
