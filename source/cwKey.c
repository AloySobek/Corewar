/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwKey.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 17:37:42 by vrichese          #+#    #+#             */
/*   Updated: 2019/09/30 18:55:08 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			cwValidateArguments(corewar_t *game, char **argv, int argc)
{
	return ;
}

void			cwInitializationKeys(corewar_t *game, char **argv, int argc)
{
	key_t		*new_keys;
	int			arg_iter;
	int			str_iter;

	if (!(new_keys	= (key_t *)malloc(sizeof(key_t))))
		cwErrorCatcher(CW_NOT_ALLOCATED, CW_KEYS);
	new_keys->load_dump				= CW_FALSE;
	new_keys->custom_id				= CW_FALSE;
	new_keys->visualizator			= CW_FALSE;
	arg_iter						= CW_BEGIN_FROM_ONE;
	while (arg_iter < argc)
	{
		if (argv[arg_iter][0] == '-')
		{
			str_iter = CW_BEGIN_FROM_ONE;
			while (argv[arg_iter][str_iter])
			{
				if (argv[arg_iter][str_iter]		== 'n')
					new_keys->custom_id		= CW_TRUE;
				else if (argv[arg_iter][str_iter]	== 'd')
					new_keys->load_dump		= CW_TRUE;
				else if (argv[arg_iter][str_iter]	== 'v')
					new_keys->visualizator	= CW_TRUE;
				else
					cwErrorCatcher(CW_NOT_VALID_KEY, CW_KEYS);
				++str_iter;
			}
			argv[arg_iter][0] = '*';
		}
		++arg_iter;
	}
	game->destructor->keys_detect	= CW_TRUE;
	game->keys						= new_keys;
}