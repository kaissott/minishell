/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karamire <karamire@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 21:19:49 by kaissramire       #+#    #+#             */
/*   Updated: 2025/05/22 17:04:09 by karamire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "../Libft/libft.h"
# include "builtins.h"
# include "error.h"
# include "exec.h"
# include "structures.h"
# include <fcntl.h> // pour open()
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

char	**ft_split_slash(char const *s, char c);
void	free_tabs(char **tab1, char **tab2);
void	fork_error(t_main *main);
void	free_files(t_main *main);

#endif
