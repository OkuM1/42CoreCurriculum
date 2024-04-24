/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokutucu <mokutucu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 14:43:19 by mokutucu          #+#    #+#             */
/*   Updated: 2023/11/23 15:32:31 by mokutucu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_assign(t_list **newlist, t_list **lastnode)
{
	*newlist = NULL;
	*lastnode = NULL;
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lastnode;
	t_list	*newlist;
	t_list	*newnode;

	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	ft_assign(&newlist, &lastnode);
	while (lst)
	{
		newnode = malloc(sizeof(t_list));
		if (newnode == NULL)
		{
			ft_lstclear(&newlist, del);
			return (NULL);
		}
		newnode->content = f(lst->content);
		newnode->next = NULL;
		if (lastnode == NULL)
			newlist = newnode;
		else
			lastnode->next = newnode;
		lastnode = newnode;
		lst = lst ->next;
	}
	return (newlist);
}
