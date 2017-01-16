/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arch64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hivian <hivian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 10:00:01 by hivian            #+#    #+#             */
/*   Updated: 2017/01/13 15:01:15 by hivian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static int			g_sect_index = 0;

static void			get_sect_index(t_env *e)
{
	size_t			i;

	e->segment = (t_segment_command_64*)e->load_cmd;
	e->section = (t_section_64 *)((char*)e->segment + sizeof(*e->segment));
	i = 0;
	while (i < e->segment->nsects)
	{
		if (!ft_strcmp((e->section + i)->sectname, SECT_TEXT))
			e->text_nsect = g_sect_index + 1;
		if (!ft_strcmp((e->section + i)->sectname, SECT_DATA))
			e->data_nsect = g_sect_index + 1;
		if (!ft_strcmp((e->section + i)->sectname, SECT_BSS))
			e->bss_nsect = g_sect_index + 1;
		g_sect_index++;
		i++;
	}
}

static void			get_mdata_sym(t_env *e)
{
	size_t			i;

	i = 0;
	e->output_arr = (char ***)malloc(sizeof(char**) * e->sym->nsyms);
	e->symbols = e->ptr + e->sym->symoff;
	e->str_table = e->ptr + e->sym->stroff;
	while (i < e->sym->nsyms)
	{
		e->output_arr[i] = (char **)malloc(sizeof(char*) * 5);
		e->output_arr[i][0] = ft_ulitoa(e->symbols[i].n_value);
		e->output_arr[i][1] = ft_itoa(e->symbols[i].n_type & N_TYPE);
		e->output_arr[i][2] = ft_strdup(e->str_table + \
			e->symbols[i].n_un.n_strx);
		e->output_arr[i][3] = ft_itoa(e->symbols[i].n_sect);
		if (e->symbols[i].n_type == N_LSYM_INDEX)
			e->output_arr[i][4] = ft_strdup("LSYM_OK");
		else
			e->output_arr[i][4] = ft_strdup("LSYM_KO");
		i++;
	}
}

void				handle_64(t_env *e)
{
	size_t			i;

	i = 0;
	e->header = (t_mach_header_64 *)e->ptr;
	e->load_cmd = (void*)e->ptr + sizeof(*e->header);
	while (i < e->header->ncmds)
	{
		e->sym = (t_symtab_command*)e->load_cmd;
		if (e->load_cmd->cmd == LC_SEGMENT_64)
			get_sect_index(e);
		if (e->load_cmd->cmd == LC_SYMTAB)
		{
			get_mdata_sym(e);
			if (!e->opt_p)
				sort_alpha(e);
			print_output(e);
			break ;
		}
		e->load_cmd = (void *)e->load_cmd + e->load_cmd->cmdsize;
		i++;
	}
	g_sect_index = 0;
}
