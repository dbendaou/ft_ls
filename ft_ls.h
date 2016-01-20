/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendaou <dbendaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/20 16:51:56 by dbendaou          #+#    #+#             */
/*   Updated: 2016/01/20 18:14:28 by dbendaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		FT_LS_H
# define	FT_LS_H

# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <unistd.h>
# include <pwd.h>
# include <grp.h>
# include <errno.h>
# include "../Libft-42/libft.h"
# include <stdio.h>

typedef struct 		s_dlst
{
	struct dirent	*str;
	struct s_dlst	*next;
	struct s_dlst	*prev;
}					t_dlst;

int		ft_ls(char *direct);


#endif
