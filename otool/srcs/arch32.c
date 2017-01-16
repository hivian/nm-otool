/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arch32.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 11:15:59 by hivian            #+#    #+#             */
/*   Updated: 2017/01/13 11:46:58 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static void			get_sect_index(t_env *e)
{
	t_section		*sect_text;
	size_t			i;

	e->segment_32 = (t_segment_command*)e->load_cmd;
	e->section_32 = (t_section*)((char*)e->segment_32 + sizeof(*e->segment_32));
	i = -1;
	while (++i < e->segment_32->nsects)
	{
		sect_text = e->section_32 + i;
		if (!ft_strcmp(sect_text->sectname, SECT_TEXT))
		{
			print_t_32(sect_text, e);
			break ;
		}
	}
}

void				handle_32(t_env *e)
{
	size_t			i;

	i = 0;
	e->header_32 = (t_mach_header*)e->ptr;
	e->load_cmd = (void*)e->ptr + sizeof(*e->header_32);
	while (i < e->header_32->ncmds)
	{
		e->sym = (t_symtab_command*)e->load_cmd;
		if (e->load_cmd->cmd == LC_SEGMENT && e->opt_t)
			get_sect_index(e);
		e->load_cmd = (void*)e->load_cmd + e->load_cmd->cmdsize;
		i++;
	}
	if (e->opt_h)
		print_h_32(e);
}
