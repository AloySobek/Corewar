/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 21:09:41 by vrichese          #+#    #+#             */
/*   Updated: 2019/09/20 19:03:50 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/vrichese/Workspace/Rus42/Algorithms/Corewar/include/corewar.h"

void			initialization_keys(corewar_t *game, char **argv, int argc)
{
	key_t		*new_keys;
	int			iter;

	if (!(new_keys = (key_t *)malloc(sizeof(key_t))))
		error_catcher(MEMORY_ALLOC_ERROR, KEYS);
	iter = 1;
	while (iter < argc)
	{
		if (argv[iter][0] == '-')
		{
			if (argv[iter][1] == 'n' && argv[iter][2] == 0)
				new_keys->custom_id			= TRUE;
			else if (argv[iter][1] == 'c' && argv[iter][2] == 0)
				new_keys->concurance_cpu	= TRUE;
			else if (argv[iter][1] == 'g' && argv[iter][2] == 0)
				new_keys->concurance_gpu	= TRUE;
			else if (argv[iter][1] == 'v' && argv[iter][2] == 0)
				new_keys->visualizator		= TRUE;
			else
				error_catcher(NOT_VALID_ARG, KEYS);
			argv[iter][0] = '*';
		}
		++iter;
	}
	game->destructor->keys_detect = TRUE;
	game->keys = new_keys;
}

//void			initialization_commands(corewar_t *game)
//{
//	commands_t	*new_commands;
//
//	if (!(new_commands = (commands_t *)malloc(sizeof(commands_t))))
//		exit(1);
//}

void			initialization_game(corewar_t **game)
{
	corewar_t	*new_game;

	if (!(new_game = (corewar_t *)malloc(sizeof(corewar_t))))
		error_catcher(MEMORY_ALLOC_ERROR, GAME);
	new_game->players_amount	= 0;
	new_game->carriages_amount	= 0;
	new_game->commands_amount	= 0;
	new_game->keys				= NULL;
	new_game->players			= NULL;
	new_game->commands			= NULL;
	new_game->arena				= NULL;
	new_game->carriages			= NULL;
	new_game->destructor		= NULL;
	*game = new_game;
}

void			initialization_destructor(corewar_t *game)
{
	destructor_t	*new_destructor;

	if (!(new_destructor = (destructor_t *)malloc(sizeof(destructor_t))))
		error_catcher(MEMORY_ALLOC_ERROR, DESTRUCTOR);
	new_destructor->self_detect			= TRUE;
	new_destructor->game_detect			= TRUE;
	new_destructor->keys_detect			= FALSE;
	new_destructor->arena_detect		= FALSE;
	new_destructor->players_detect		= FALSE;
	new_destructor->commands_detect 	= FALSE;
	new_destructor->carriages_detect	= FALSE;
	game->destructor					= new_destructor;
}

void	read_from_reg_to_buf(carriage_t *carriage, int reg_num)
{
	int iter;
	int buf_iter;

	buf_iter = 0;
	iter = --reg_num * REG_SIZE;
	while (buf_iter < REG_SIZE)
	{
		carriage->reg_buf[buf_iter] = carriage->registers[iter];
		++iter;
		++buf_iter;
	}
}

int				main(int argc, char **argv)
{
	corewar_t	*game;

	if (argc < 2) {return (0);}
	initialization_game			(&game);
	initialization_destructor	(game);
	initialization_keys			(game, argv, argc);
	initialization_players		(game, argv, argc);
	initialization_carriages	(game);
	initialization_arena		(game);
	//initialization_commands		(game);
	//arrange_units(game);
	//introduce_players(game);
	//here_we_go(game);
	return (0);
}