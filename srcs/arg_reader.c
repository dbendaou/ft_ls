/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendaou <dbendaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/25 14:48:05 by dbendaou          #+#    #+#             */
/*   Updated: 2016/05/23 16:58:48 by dbendaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static unsigned int		arg_reader(char *args, t_params *tmp)
{
	unsigned int	i_ar;
	int				i;

	i = 0;
	i_ar = 0;
	while (args[i])
	{
		if (args[i] == 'l')
			i_ar = i_ar | OPT_L;
		else if (args[i] == 'R')
			i_ar = i_ar | OPT_RC;
		else if (args[i] == 'a')
			i_ar = i_ar | OPT_A;
		else if (args[i] == 'r')
			i_ar = i_ar | OPT_RV;
		else if (args[i] == 't')
			i_ar = i_ar | OPT_T;
		else if (args[i] != '-')
		{
			tmp->arg = args[i];
			return (ILL_OPT);
		}
		i++;
	}
	return (i_ar);
}

t_params				*get_params(int size, char **av)
{
	int				i;
	t_params		*tmp;

	tmp = (t_params *)malloc(sizeof(t_params));
	tmp->prms = 0;
	tmp->count = 0;
	i = 1;
	while (i < size)
	{
		if (ft_strcmp(av[i], "--") == 0)
		{
			tmp->prms = NO_PRM;
			return (tmp);
		}
		tmp->prms = (av[i][0] == '-') ? tmp->prms | arg_reader(av[i], tmp)
			: tmp->prms;
		if (IS_LEG(tmp->prms))
		{
			arg_error(tmp->arg);
			free(tmp);
			return (NULL);
		}
		i++;
	}
	return (tmp);
}
