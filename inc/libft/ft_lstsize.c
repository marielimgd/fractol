/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:16:13 by marieli           #+#    #+#             */
/*   Updated: 2025/03/19 18:49:11 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_lstsize(t_list *lst)
{
	int	node_count;

	node_count = 0;
	while (lst != NULL)
	{
		node_count++;
		lst = lst->next;
	}
	return (node_count);
}
