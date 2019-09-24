/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 19:14:53 by vrichese          #+#    #+#             */
/*   Updated: 2019/09/24 17:36:38 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			introduce_players(corewar_t *game)
{
	player_t	*tmp;
	int iter;

	iter = 0;
	tmp = game->players;
	printf("Introducing contestants...\n");
	while (game->players)
	{
		printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\")\n",
		game->players->id, game->players->code_size,
		game->players->name, game->players->comment);
		game->players = game->players->next;
		++iter;
	}
}

void			print_arena(corewar_t *game)
{
	int			border;
	int			i;

	border	= sqrt(MEM_SIZE);
	i		= 0;
	while (i < MEM_SIZE)
	{
		printf("%.2x ", game->arena->field[i]);
		if ((i + 1) % border == 0 && i > 10)
			printf("\n");
		++i;
	}
}

void			arrange_units(corewar_t *game)
{
	player_t	*iter;
	int			player_location;
	int			memory_step;
	int			code_iter;
	int			test;

	memory_step = MEM_SIZE / game->players_amount;
	iter = game->players;
	test = 0;
	while (iter)
	{
		code_iter = 0;
		player_location = memory_step * test;
		game->carriages->current_location = player_location;
		while (player_location < memory_step * test + CHAMP_MAX_SIZE)
			game->arena->field[player_location++] = iter->code[code_iter++];
		iter = iter->next;
		game->carriages = game->carriages->prev;
		++test;
	}
}

void			initialization_arena(corewar_t *game)
{
	arena_t		*new_arena;

	if (!(new_arena = (arena_t *)malloc(sizeof(arena_t))))
		error_catcher(MEMORY_ALLOC_ERROR, ARENA);
	if (!(new_arena->field = (unsigned char *)malloc(sizeof(unsigned char) * MEM_SIZE)))
		error_catcher(MEMORY_ALLOC_ERROR, ARENA);
	if (!(new_arena->value_buf1 = (unsigned char *)malloc(sizeof(unsigned char) * REG_SIZE)))
		error_catcher(MEMORY_ALLOC_ERROR, ARENA);
	if (!(new_arena->value_buf2 = (unsigned char *)malloc(sizeof(unsigned char ) * REG_SIZE)))
		error_catcher(MEMORY_ALLOC_ERROR, ARENA);
	if (!(new_arena->value_buf3 = (unsigned char *)malloc(sizeof(unsigned char ) * REG_SIZE)))
		error_catcher(MEMORY_ALLOC_ERROR, ARENA);
	if (!(new_arena->address_buf = (unsigned char *)malloc(sizeof(unsigned char ) * REG_SIZE)))
		error_catcher(MEMORY_ALLOC_ERROR, ARENA);
	ft_memset(new_arena->field, 0, MEM_SIZE);
	new_arena->last_survivor		= game->players;
	new_arena->last_carriage		= game->carriages;
	new_arena->cycle_amount 		= 0;
	new_arena->live_amount			= 0;
	new_arena->check_amount			= 0;
	new_arena->cycle_to_die			= CYCLE_TO_DIE;
	game->arena						= new_arena;
	game->destructor->arena_detect	= TRUE;
	arrange_units					(game);
}