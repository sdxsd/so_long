#include <mlx.h>
#include <unistd.h>
#include <stdio.h>

int nederland(void *win,int w,int h, void *mlx)
{
	int   x;
	int   y;
	int   color;

	color = 0x0003DA5;
	y = h;
	while (y--)
	{
		x = w;
		while (x--)
		{
			if (y == 200)
				color = 0x00C8102E;
			if (y == 400)
				color = 0xFFFFFFFF;
			mlx_pixel_put(mlx, win, x, y, color);
		}
	}
	return (0);
}


int	main(void)
{
	void	*mlx_win;
	void	*img;
	void	*mlx;


	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 800, 600, "Nederland");
	img = mlx_new_image(mlx, 800, 600);

	nederland(mlx_win, 800, 600, mlx);
	mlx_loop(mlx);
}
