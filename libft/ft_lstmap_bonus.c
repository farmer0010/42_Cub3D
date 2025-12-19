/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyoukim <juyoukim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 17:37:27 by juyoukim          #+#    #+#             */
/*   Updated: 2025/04/16 11:15:59 by juyoukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*map_lst;
	t_list	*map_node;
	void	*map_content;

	map_lst = NULL;
	while (lst)
	{
		map_content = f(lst->content);
		map_node = ft_lstnew(map_content);
		if (!map_node)
		{
			ft_lstclear(&map_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&map_lst, map_node);
		lst = lst->next;
	}
	return (map_lst);
}
