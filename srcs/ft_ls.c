/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendaou <dbendaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/22 18:35:39 by dbendaou          #+#    #+#             */
/*   Updated: 2016/05/22 19:22:48 by dbendaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	**get_nextls(t_file *current, int *cnt, t_params *params)
{
	char	**next_ls;
	int		i;
	t_file	*dir;
	char	*name;

	dir = current;
	i = 0;
	if ((*cnt = count_dr(dir)) == 0)
		return (NULL);
	next_ls = (char **)malloc(sizeof(char *) * (count_dr(dir) + 1));
	while (dir)
	{
		name = get_filename(dir->f_path);
		if (S_ISDIR(dir->f_mode) && (ft_strcmp(name, "..") != 0)
			&& (ft_strcmp(name, ".") != 0) && is_print(dir, params)
			&& dir->error != 1)
		{
			next_ls[i] = ft_strsub(dir->f_path, 0, ft_strlen(dir->f_path));
			i++;
		}
		dir = dir->next;
	}
	*cnt = i;
	next_ls[i] = NULL;
	return (next_ls);
}

void	main_ls(t_file **files, t_params *params)
{
	open_ifdir(files, params);
	if (IS_RV(params->prms))
		reverse_list(files);
	if (!IS_RC(params->prms))
		printer(*files, params);
}

int		ft_ls(int ac, char **av, t_params *params)
{
	t_file		*files;
	int			i;
	char		**next_ls;
	int			f;

	i = 0;
	if (av[0] == NULL)
		return (0);
	next_ls = NULL;
	if ((params = (params == NULL) ? get_params(ac, av) : params) == NULL)
		return (0);
	files = get_file(ac, av, params);
	main_ls(&files, params);
	if (IS_RC(params->prms))
	{
		recursive(&files, params, &i, &next_ls);
		f = -1;
		while (f++ < i)
			ft_strdel(&next_ls[f]);
		free(next_ls);
	}
	return (1);
}

int		main(int ac, char **av)
{
	t_params *params;

	params = NULL;
	ft_ls(ac, av, params);
	if (params)
		free(params);
	return (1);
}
