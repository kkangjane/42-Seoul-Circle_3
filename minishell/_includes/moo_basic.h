/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moo_basic.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jae-kang <jae-kang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 13:33:55 by jae-kang          #+#    #+#             */
/*   Updated: 2024/01/21 15:24:52 by jae-kang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOO_BASIC_H
# define MOO_BASIC_H

# define PIPE 1
# define HEREDOC 2
# define REDIRECT 4
# define INPUT 8
# define OUTPUT 16
# define APPEND 32
# define BUFFER_SIZE	100

# include <unistd.h>
# include "../libft/libft.h"
# include <stdlib.h>
# include <stdio.h>

char	**g_env;

typedef struct s_file_lst
{
	char				*filename;
	int					io_flag;
	struct s_file_lst	*next;
}	t_file_lst;

typedef struct s_cmd
{
	int				idx;
	char			**cmd;
	t_file_lst		*files;
	char			**heredoc;
	int				pid;
	int				in_fd;
	int				out_fd;
	int				infile_fd;
	int				outfile_fd;
	int				error;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_buf
{
	char	*buf;
	char	*saved;
	int		buf_size;
	int		saved_size;
}	t_buf;

typedef struct s_token
{
	char			*buf;
	int				attr;
	struct s_token	*next;
}	t_token;

t_cmd		*cmd_idx(t_cmd *cmd, int idx);
char		*find_command(char **cmd_args);
int			free_str(char *s1, char *s2, char *s3, int ret);
long long	ft_atol(const char *str);
void		init_moo(char **argv, int argc, char **envp);
int			perror_msg(const char *msg);
int			print_error(char *f, char *wrong_s, char *msg, int exit_code);
void		error_exit(const char *string);

#endif