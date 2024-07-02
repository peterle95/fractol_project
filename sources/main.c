/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmolzer <pmolzer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 13:14:30 by pmolzer           #+#    #+#             */
/*   Updated: 2024/07/02 19:04:18 by pmolzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

#include <string.h>

void draw_fractal(t_data *data)
{
    if (data->fractal_type == MANDELBROT)
        draw_mandelbrot(data);
    else if (data->fractal_type == JULIA)
        draw_julia(data);
    // Add more fractal types here if needed
}
int close_window(t_data *data)
{
    mlx_destroy_image(data->mlx, data->img);
    mlx_destroy_window(data->mlx, data->win);
    mlx_destroy_display(data->mlx);
    free(data->mlx);
    exit(0);
}

int key_hook(int keycode, t_data *data)
{
    if (keycode == 65307)  // ESC key
        close_window(data);
    else if (keycode == 49) // '1' key
        data->fractal_type = MANDELBROT;
    else if (keycode == 50) // '2' key
        data->fractal_type = JULIA;
    else
        return (0);
    draw_fractal(data);
    return (0);
} 

/*We create an is_valid_float function to check if a string represents a 
valid floating-point number. This function:

Allows an optional leading '+' or '-' sign.
Ensures there's at most one decimal point.
Checks that all other characters are digits.
Ensures the string is not empty.*/
int is_valid_float(const char *str)
{
    int i = 0;
    int dot_count = 0;

    if (str[i] == '-' || str[i] == '+')
        i++;
    while (str[i])
    {
        if (str[i] == '.')
        {
            dot_count++;
            if (dot_count > 1)
                return (0);
        }
        else if (str[i] < '0' || str[i] > '9')
            return (0);
        i++;
    }
    return (i > 0);
}

/*We create a separate parse_args function to handle the argument parsing. This keeps the main function clean and makes the code more modular.
We check if there's at least one argument (the program name is argc[0], so we need argc >= 2).
We use strcmp to check if the first argument is "mandelbrot" or "julia". This is simple and straightforward.
For the Mandelbrot set, we don't need additional parameters, so we just set the fractal type.
We check if exactly 3 arguments are provided (program name, "julia", and two parameters).
We validate each parameter using is_valid_float.
We convert the parameters to doubles using atof.
We check if the parameters are within the range -2 to 2, which is a common range for interesting Julia sets.

We return 0 from parse_args if:

The fractal type is not recognized.
The Julia set is selected but the number of arguments is incorrect.
The Julia set parameters are not valid floats.
The Julia set parameters are out of the acceptable range.*/
int parse_args(int argc, char **argv, t_data *data)
{
    if (argc < 2)
        return (0);
    
    if (ft_strcmp(argv[1], "mandelbrot") == 0)
    {
        data->fractal_type = 1;
    }
    else if (ft_strcmp(argv[1], "julia") == 0)
    {
        data->fractal_type = 2;
        if (argc == 4)
        {
            data->julia_x = ft_atof(argv[2]);
            data->julia_y = ft_atof(argv[3]);
            if (data->julia_x == -42.0 || data->julia_y == -42.0 ||
                data->julia_x < -2.0 || data->julia_x > 2.0 ||
                data->julia_y < -2.0 || data->julia_y > 2.0)
                return (0);
        }
        else if (argc != 2)
            return (0);
    }
    else
        return (0);
    
    return (1);
}

int main(int argc, char **argv)
{
    t_data data;

    if (!parse_args(argc, argv, &data))
    {
        printf("Usage: %s [mandelbrot | julia <real> <imaginary>]\n", argv[0]);
        printf("Julia set parameters must be between -2 and 2\n");
        return (1);
    }
    init_data(&data);
    data.mlx = mlx_init();
    if (!data.mlx)
        return (1);

    data.win = mlx_new_window(data.mlx, WIN_WIDTH, WIN_HEIGHT, "Fract'ol");
    if (!data.win)
    {
        mlx_destroy_display(data.mlx);
        free(data.mlx);
        return (1);
    }

    data.img = mlx_new_image(data.mlx, WIN_WIDTH, WIN_HEIGHT);
    data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
    draw_fractal(&data);

    mlx_hook(data.win, 17, 0, (int (*)())close_window, &data);
    mlx_key_hook(data.win, key_hook, &data);

    mlx_loop(data.mlx);
    return (0);
} 