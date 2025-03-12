
#ifndef ANIMATOR_H
# define ANIMATOR_H

# include "../../MLX42/include/MLX42/MLX42.h"
# include "../../libft/libft.h"

typedef struct s_animator {
    mlx_t *mlx;
    mlx_image_t *frames[50];
    int max_frames;
    int current_frame;
    double last_update_time;
    double frame_time;
    bool is_playing;
    bool is_looping;
    bool is_hidden;
} t_animator;


t_animator *init_animator(mlx_t *mlx, int max_frames, bool is_looping, bool is_hidden);

void    anim_load_frames(t_animator *animator, t_list **graphics);

void    anim_update(t_animator *animator);

void    anim_render(t_animator *animator);

void    anim_play(t_animator *animator);

#endif