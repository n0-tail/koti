/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikkane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 10:39:28 by anikkane          #+#    #+#             */
/*   Updated: 2020/03/09 10:39:29 by anikkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "keys.h"
#include <stdbool.h> 


int     end(char *reason)
{
    ft_putendl(reason);
    return (1);
}

int     main(int argc, char **argv)
{
    void        *mlx_ptr;
    t_code       *f_code;
    char        *mandelbrot;
    t_fractal   *f_data;

    mlx_ptr = mlx_init();
    if (argc < 2)
        return (end("too few arguments"));
    f_code = fractal_check(argv[1]);
    if (f_code->name == NULL)
        return (end("wrong fractal name"));
        mandelbrot = ft_strdup("mandelbrot");
    if (ft_strcmp(f_code->name, mandelbrot) == 0)
    {
        f_data = init(mlx_ptr);
        	draw_fractal_part(f_data);
		mlx_put_image_to_window(f_data->mlx, f_data->win, f_data->image, 0, 0);
		   printf("\n%c\n", f_data->data_addr[0]);
    mlx_loop(mlx_ptr);
    }



    return (0);

}


t_color	get_color(int iteration, t_fractal *f_data)
{
	t_color	color;
	double	t;
//ft_putendl("int iteration: ");
			//ft_putnbr(iteration);
			//ft_putchar('\n');
	
	t = (double)iteration / f_data->max_iteration;
	
	/*
	color.channel[0] = 0;
	color.channel[1] = 11;
	color.channel[2] = 12;
	color.channel[3] = 15;
	*/
	color.channel[0] = 0;
	color.channel[(0 + f_data->color_shift) % 3 + 1] =
		(int8_t)(9 * (1 - t) * pow(t, 3) * 250);
	//	(int8_t)(200);
	color.channel[(1 + f_data->color_shift) % 3 + 1] =
		(int8_t)(15 * pow((1 - t), 2) * pow(t, 2) * 250);
	//(int8_t)(50);
	color.channel[(2 + f_data->color_shift) % 3 + 1] =
		(int8_t)(8.5 * pow((1 - t), 3) * t * 250);
	//(int8_t)(0);
	//ft_putendl("color : ");
	//ft_putnbr(color.channel[1]);
	//ft_putchar('\n');
	
		
	return (color);
}


void	draw_fractal_part(t_fractal *f_data)
{
	int			y;
	int			x;
	t_color		color;

	y = 0;
	//y = f->start_line;

	f_data->factor = init_complex(
		(f_data->max.re - f_data->min.re) / (WIDTH - 1),
		(f_data->max.im - f_data->min.im) / (HEIGHT - 1));
	while (y < HEIGHT)
	{
		f_data->c.im = f_data->max.im - y * f_data->factor.im;
		x = 0;
		while (x < WIDTH)
		{
			f_data->c.re = f_data->min.re + x * f_data->factor.re;

			color = get_color(iterate_mandelbrot(f_data), f_data);
			
			put_pixel(f_data, x, y, color);
	
			x++;
		}
		y++;
	}
		  printf("\n%s\n", f_data->data_addr);
}

void	put_pixel(t_fractal *f_data, int x, int y, t_color color)
{
	int i;

	
	//f (x < WIDTH && y >= 0 && y < HEIGHT)
	{
		i = (x * f_data->bits_per_pixel / 8) + (y * f_data->size_line);
	//	printf("%d\n", i);
		f_data->data_addr[i] = color.channel[3];
		f_data->data_addr[++i] = color.channel[2];
		f_data->data_addr[++i] = color.channel[1];
		f_data->data_addr[++i] = color.channel[0];
//	printf("%hhd", (color.channel[2]));
//	ft_putchar('\n');
	}

}

void set_data(t_fractal *f_data)
{
	
//	f_data->bits_per_pixel /= 8;
	f_data->size_line = 1000;
	f_data->endian = 0;
	f_data->max_iteration = 50;
	f_data->min = init_complex(-2.0, -2.0);
	f_data->max.re = 2.0;
	f_data->max.im = f_data->min.im
		+ (f_data->max.re - f_data->min.re) * HEIGHT / WIDTH;
	f_data->k = init_complex(-0.4, 0.6);
	f_data->color_shift = 2;
	
	
}

t_complex	init_complex(double re, double im)
{
	
	t_complex	complex;
	complex.re = re;
	complex.im = im;
	return (complex);
}

int		iterate_mandelbrot(t_fractal *f_data)
{
	int			iteration;
	t_complex	z;
	iteration = 0;
	z = init_complex(f_data->c.re, f_data->c.im);
	while (pow(z.re, 2.0) + pow(z.im, 2.0) <= 4
		&& iteration < f_data->max_iteration)
	{
	
		z = init_complex(
			pow(z.re, 2.0) - pow(z.im, 2.0) + f_data->c.re,
			2.0 * z.re * z.im + f_data->c.im);
		iteration++;
	}
	return (iteration);
}
/*
void		mandelbrot_viewport(t_viewport *v)
{
	v->xmin = -2.0f;
	v->xmax = 1.0f;
	v->ymin = -1.0f;
	v->ymax = 1.0f;
	v->offx = -0.5f;
}
*/
/*

static double	interpolate(double start, double end, double interpolation)
{
	return (start + ((end - start) * interpolation));
}

int				zoom(int button, int x, int y, t_fractal *f_data)
{
	t_complex	mouse;
	double		interpolation;
	double		zoom;

	//if (!f_data->is_help
	//	&& (button == MOUSE_SCROLL_UP || button == MOUSE_SCROLL_DOWN))
	//{
		mouse = init_complex(
			(double)x / (WIDTH / (f_data->max.re - f_data->min.re))
				+ f_data->min.re,
			(double)y / (HEIGHT / (f_data->max.im - f_data->min.im))
				* -1 + f_data->max.im);
		if (button == MOUSE_SCROLL_UP)
			zoom = 0.80;
		else
			zoom = 1.20;
		interpolation = 1.0 / zoom;
		f_data->min.re = interpolate(mouse.re, f_data->min.re, interpolation);
		f_data->min.im = interpolate(mouse.im, f_data->min.im, interpolation);
		f_data->max.re = interpolate(mouse.re, f_data->max.re, interpolation);
		f_data->max.im = interpolate(mouse.im, f_data->max.im, interpolation);
		draw_fractal(f_data);
//	}
	return (0);
}*/