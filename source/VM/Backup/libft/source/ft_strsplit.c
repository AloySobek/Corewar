/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormund <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 16:51:01 by cormund           #+#    #+#             */
/*   Updated: 2019/06/29 14:42:33 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		clean_memory(char **mas, size_t size)
{
	while (size)
		free(mas[size--]);
	free(mas);
}

static size_t	size_str(const char *str, char c)
{
	size_t		count;

	count = 0;
	while (str[count] && str[count] != c)
		count++;
	return (count);
}

static int		alloc_memory(char **mas, char const *s, char c, size_t count)
{
	size_t		i;
	size_t		len;

	i = 0;
	while (count--)
	{
		while (*s == c)
			s++;
		len = size_str(s, c);
		mas[i] = ft_strnew(len);
		if (!mas[i])
		{
			clean_memory(mas, i);
			return (1);
		}
		mas[i] = ft_strncpy(mas[i], s, len);
		i++;
		s += len;
	}
	mas[i] = NULL;
	return (0);
}

static size_t	count_words(char const *s, char c)
{
	size_t		count_w;
	int			check_in;

	count_w = 0;
	check_in = 0;
	while (*s)
	{
		if (*s == c)
			check_in = 0;
		else if (check_in == 0)
		{
			count_w++;
			check_in = 1;
		}
		s++;
	}
	return (count_w);
}

char			**ft_strsplit(char const *s, char c)
{
	size_t		count_s;
	char		**mas;

	if (!s)
		return (NULL);
	count_s = count_words(s, c);
	mas = (char **)ft_memalloc(sizeof(char *) * (count_s + 1));
	if (!mas)
		return (NULL);
	if (alloc_memory(mas, s, c, count_s))
		return (NULL);
	else
		return (mas);
}
