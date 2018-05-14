
#gcc -I ./minilibx_macos  -L ./minilibx_macos -l mlx -framework OpenGL -framework AppKit
gcc  src/*.c -I ./includes -I ./libft/includes -L ./libft/ -l ft -I ./minilibx_macos -L ./minilibx_macos -l mlx -framework OpenGL -framework AppKit -o wolf3d
