/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 09:18:15 by hivian            #+#    #+#             */
/*   Updated: 2017/01/13 11:41:36 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void		swap_alpha(char **str1, char **str2)
{
	char		*tmp;

	tmp = *str1;
	*str1 = ft_realloc(*str2, ft_strlen(*str2));
	*str2 = ft_realloc(tmp, ft_strlen(tmp));
}

void			sort_alpha(t_env *e)
{
	size_t		i;

	i = 0;
	while (i < e->sym->nsyms - 1)
	{
		if (ft_strcmp(e->output_arr[i][2], e->output_arr[i + 1][2]) > 0)
		{
			swap_alpha(&(e->output_arr[i][4]), &(e->output_arr[i + 1][4]));
			swap_alpha(&(e->output_arr[i][3]), &(e->output_arr[i + 1][3]));
			swap_alpha(&(e->output_arr[i][2]), &(e->output_arr[i + 1][2]));
			swap_alpha(&(e->output_arr[i][1]), &(e->output_arr[i + 1][1]));
			swap_alpha(&(e->output_arr[i][0]), &(e->output_arr[i + 1][0]));
			i = -1;
		}
		i++;
	}
}
