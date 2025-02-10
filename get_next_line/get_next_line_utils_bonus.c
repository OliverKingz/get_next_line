/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 20:35:11 by ozamora-          #+#    #+#             */
/*   Updated: 2024/11/13 15:37:07 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int		ft_lst_hasnextline(t_list **lst);
void	ft_lst_new_addback(void *content, t_list **lst, int bytes_read);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstclear(t_list **lst, void (*del)(void *));
size_t	ft_strlen(const char *s);

/**
 * ft_lst_hasnextline - Checks if there is a newline in the list.
 * @param lst: A pointer to the list to check for a newline.
 * 
 * Return: 
 *  - The index of the newline if found. It is also the resulting string lenght.
 *  - Returns -1 if no newline is present.
 * Description:
 *  - Iterates through the list and checks for a newline character for each node.
 *  - Returns the position of the newline or -1 if not found.
 */
int	ft_lst_hasnextline(t_list **lst)
{
	t_list	*current;
	int		i;
	int		str_len;

	if (*lst == NULL || lst == NULL)
		return (-1);
	current = *lst;
	str_len = 0;
	while (current != NULL)
	{
		i = 0;
		while (((char *)current->content)[i] != '\0')
		{
			if (((char *)current->content)[i] == '\n')
				return (str_len + i);
			i++;
		}
		current = current->next;
		str_len = str_len + i;
	}
	return (-1);
}

/* ************************************************************************** */
/*                        Functions from ozamora-'s Libft
 * 
 * List Handling Functions:
 * - ft_lst_new_addback: Adds a new element with content to the end of the list.
 *                       Combination of lst_add and lst_addback from Libft
 * - ft_lstlast: Returns the last element of the list.
 * - ft_lstclear: Clears and frees the entire list.
 *
 * String Utility Functions:
 * - ft_strlen: Returns the length of a string.
 */
/* ************************************************************************** */

void	ft_lst_new_addback(void *content, t_list **lst, int bytes_read)
{
	t_list	*new;
	t_list	*last;
	int		i;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return ;
	new->next = NULL;
	new->content = (char *)malloc((bytes_read + 1) * sizeof(char));
	if (new->content == NULL)
		return (free(new));
	i = 0;
	while (i < bytes_read)
	{
		((char *)new->content)[i] = ((char *)content)[i];
		i++;
	}
	((char *)new->content)[i] = '\0';
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new;
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current_next;

	if (lst == NULL || *lst == NULL || del == NULL)
		return ;
	while (*lst != NULL)
	{
		current_next = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = current_next;
	}
	*lst = NULL;
}

size_t	ft_strlen(const char *s)
{
	int	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return ((size_t)len);
}

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*current;

	if (lst == NULL)
		return (NULL);
	current = lst;
	while (current->next != NULL)
		current = current->next;
	return (current);
}
