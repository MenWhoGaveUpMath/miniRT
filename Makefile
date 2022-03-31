# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bahn <bahn@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/14 13:30:16 by bahn              #+#    #+#              #
#    Updated: 2022/03/31 14:57:36 by bahn             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	miniRT

OS			=	$(shell uname -s)

ifeq ($(OS), Linux)
	MLX_PATH	= ./minilibx-linux
	MLX_FLAGS	= -Lminilibx-linux/ -lmlx -lX11 -lXext -lm -lbsd -O3
else
	MLX_PATH	= ./minilibx_opengl_20191021
	MLX_FLAGS	= -Lminilibx_opengl_20191021/ -lmlx -lm -framework OpenGL -framework AppKit -O3
	
# MLX_PATH	= ./minilibx_mms_20200219
# MLX_FLAGS	= -Lminilibx_mms_20200219/ -lmlx -lm -framework OpenGL -framework AppKit -O3
endif

LIBFT_PATH		= ./libft/
LIBFT_LINK		= -Llibft -lft

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -g

INCFLAGS	=	-I./includes -I./libft

ifeq ($(OS), Linux)
INCFLAGS	+=	-I./minilibx-linux
else
INCFLAGS	+=	-I./minilibx_opengl_20191021
#INCFLAGS	+=	-I./minilibx_mms_20200219
endif

SRCS_DIR	=	./srcs/
OBJS_DIR	=	./objs/
SRCS_FNAME	=	hooks/minirt_close.c \
				hooks/minirt_esc.c \
				hooks/camera_movement.c \
				color/color.c \
				vector/vector.c \
				vector/vector_operation.c \
				ray/ray.c \
				camera/camera.c \
				canvas/canvas.c \
				concept/concept.c \
				object/object.c \
				object/hit.c \
				object/set_face_normal.c \
				object/sphere/sphere.c \
				object/plane/plane.c \
				object/cylinder/cylinder.c \
				object/square/square.c \
				light/light.c \
				main.c \
				minirt_world.c \
				minirt_free.c \
				\
				parse_jseol/get_next_line_utils.c \
				parse_jseol/get_next_line.c \
				parse_jseol/parse_color3.c \
				parse_jseol/parse_file.c \
				parse_jseol/parse_objects.c \
				parse_jseol/parse_scene.c \
				parse_jseol/split_utils.c \
				parse_jseol/ft_atod.c \
				parse_jseol/ft_isspace.c
SRCS		=	$(addprefix $(SRCS_DIR), $(SRCS_FNAME))
OBJS		=	$(SRCS:.c=.o)

ifeq ($(OS), Linux)
.c.o : $(SRCS)
	$(CC) $(CFLAGS) -c $< $(INCFLAGS) $(MLX_FLAGS) $(LIBFT_LINK) -o $@
else
.c.o : $(SRCS)
	$(CC) $(CFLAGS) $(INCFLAGS) -c $< -o $@
endif

$(NAME)		:	$(OBJS)
			$(MAKE) all -C $(MLX_PATH)
			$(MAKE) all -C $(LIBFT_PATH)
ifeq ($(OS), Linux)
			$(CC) $(CFLAGS) $^ $(INCFLAGS) $(LIBFT_LINK) $(MLX_FLAGS) -o $@
else
			$(CC) $(CFLAGS) $(INCFLAGS) $(LIBFT_LINK) $(MLX_FLAGS) -o $@ $^
endif

all			:	$(NAME)

clean		:	
				$(RM) $(OBJS) 
				$(MAKE) clean -C $(LIBFT_PATH)

fclean		:	clean
				$(RM)
				$(RM) $(NAME)
				$(MAKE) clean -C $(MLX_PATH)
				$(MAKE) fclean -C $(LIBFT_PATH)

re			:	fclean all

.PHONY		:	all clean fclean re
