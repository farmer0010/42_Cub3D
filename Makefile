# --- Program Name ---
NAME        = cub3D

# --- Commands & Flags ---
CC          = cc
CFLAGS      = -Wall -Wextra -Werror
# GNL 버퍼 크기 설정 (컴파일 타임 상수)
CFLAGS      += -D BUFFER_SIZE=42
RM          = rm -f

# --- Directories ---
LIBFT_DIR   = ./libft
MLX_DIR     = ./minilibx-linux
SRCS_DIR    = ./srcs
INCS_DIR    = ./includes

# --- Include & Library Paths ---
# -I: 헤더 파일을 찾을 경로
INCLUDES    = -I$(INCS_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)

# -L: 라이브러리 폴더 위치, -l: 라이브러리 이름(lib 제외)
# Linux 필수: -lXext -lX11 -lm (수학)
LIBS        = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# --- Source Files ---
SRCS        = $(wildcard srcs/*.c)
# 귀찮아서 일단 와일드 카드로 바꾸고 나중에 C 파일 다 정리되면 다시 고치자
# SRC_FILES   = main.c \
#               parsing.c \
#               get_next_line.c \
#               get_next_line_utils.c \
# 			  validate_map.c

# SRCS        = $(addprefix $(SRCS_DIR)/, $(SRC_FILES))
OBJS        = $(SRCS:.c=.o)

# --- Rules ---

all: $(NAME)

# 실행 파일 생성 규칙
# 1. libft와 mlx를 먼저 make 합니다.
# 2. 우리 프로젝트의 오브젝트 파일들과 라이브러리를 링크합니다.
$(NAME): $(OBJS)
	@echo "🔨 Compiling Libft..."
	@make -C $(LIBFT_DIR)
	@echo "🔨 Compiling MiniLibX..."
	@make -C $(MLX_DIR)
	@echo "🔨 Linking $(NAME)..."
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@echo "✅ Build Success!"

# .c -> .o 컴파일 규칙
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# 청소 규칙
clean:
	@make -C $(LIBFT_DIR) clean
	@make -C $(MLX_DIR) clean
	$(RM) $(OBJS)
	@echo "🧹 Objects cleaned"

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)
	@echo "🧹 Executable cleaned"

re: fclean all

.PHONY: all clean fclean re
