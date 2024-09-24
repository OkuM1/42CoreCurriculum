/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afoth <afoth@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 20:07:35 by mokutucu          #+#    #+#             */
/*   Updated: 2024/05/28 16:06:37 by afoth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_words(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			count++;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

/*static void	ft_free(char **array)
{
	size_t	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}*/

static void	*ft_allocate(const char *s, int start, int end)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((end - start + 1) * sizeof(char));
	while (start < end)
		word[i++] = s[start++];
	word[i] = '\0';
	return (word);
}

static void	assign(size_t *i, size_t *j, int *index)
{
	*i = 0;
	*j = 0;
	*index = -1;
}

char	**ft_split(const char *s, char c)
{
	char	**array;
	size_t	i;
	size_t	j;
	int		index;

	array = malloc((ft_words(s, c) + 1) * sizeof(char *));
	if (!s || !array)
		return (NULL);
	assign(&i, &j, &index);
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == ft_strlen(s)) && index >= 0)
		{
			array[j++] = ft_allocate(s, index, i);
			index = -1;
		}
		i++;
	}
	array[j] = NULL;
	return (array);
}
