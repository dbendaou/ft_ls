/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendaou <dbendaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/20 16:32:31 by dbendaou          #+#    #+#             */
/*   Updated: 2016/01/20 18:14:26 by dbendaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_ls.h"

int 	ft_ls(char *direct)
{
	char 			*path = NULL;
	DIR 			*p_dir;
	struct dirent	*s_dir;
	t_dlst			*begin;
	t_dlst			*tmp;
	char 			*stmp;

	stmp = ft_strjoin(direct, "/");
	begin = (t_dlst *)malloc(sizeof(t_dlst));
	begin->next = NULL;
	begin->prev = NULL;
	tmp = begin;
	if (!(p_dir = opendir(direct)))
		perror("");
	while ((tmp->str = readdir(p_dir)))
	{
		tmp->next = (t_dlst *)malloc(sizeof(t_dlst));
		tmp->next->prev = tmp;
		tmp->next->next = NULL;
		tmp->next->str = NULL;
		tmp = tmp->next;
	}
	closedir(p_dir);
	tmp = begin;
	while (tmp->str)
	{
		printf("%s\n", tmp->str->d_name);
		tmp = tmp->next;
	}
	tmp = begin;
	while (tmp->str)
	{
		if (tmp->str->d_type == DT_DIR && tmp->str->d_name[0] != '.')
		{
			path = ft_strjoin(stmp, tmp->str->d_name);
			printf("JE VEUX OUVRIR : %s\n",tmp->str->d_name);
			ft_ls(path);
		}

		tmp = tmp->next;
	}
	return (1);
	
}
int 	main(int ac, char **av)
{
	ft_ls(av[1]);
}