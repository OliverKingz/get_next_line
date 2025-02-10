/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:19:19 by ozamora-          #+#    #+#             */
/*   Updated: 2024/11/13 16:00:57 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

/* ************************************************************************** */

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

/* ************************************************************************** */

# include <fcntl.h>  // For file control options and constants like O_RDONLY
# include <stdio.h>  // For printf
# include <stdlib.h> // For dynamic memory allocation (malloc, free) and size_t.
# include <unistd.h> // For system calls like write, open, read, close.

/* ************************************************************************** */

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/* ************************************************************************** */
/*
 * Get Next Line Functions:
 * - get_next_line: Reads a line from the file descriptor.
 * 
 * GNL static Functions:
 * - read_and_store: Reads from the fd with a buffer and stores the data in lst.
 * - process_line: Processes the line depending if it has a newline or is EOF. 
 * - ft_lst_tostr: Converts list content into a string (len, malloc and fill)
 * - fill_str: Auxiliar of lst_tostr. Fills a string with content from the list.
 *
 *                      Functions from ozamora-'s Libft
 * 
 * List Handling Functions:
 * - ft_lst_hasnextline: Checks if the line contains a newline, returns where. 
 * - ft_lst_new_addback: Adds a new element with content to the end of the list.
 *                       Combination of lst_add and lst_addback from Libft
 * - ft_lstlast: Returns the last element of the list.
 * - ft_lstclear: Clears and frees the entire list.
 *
 * String Utility Functions:
 * - ft_strlen: Returns the length of a string.
 */
/* ************************************************************************** */

char	*get_next_line(int fd);

int		ft_lst_hasnextline(t_list **lst);
void	ft_lst_new_addback(void *content, t_list **lst, int bytes_read);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstclear(t_list **lst, void (*del)(void *));
size_t	ft_strlen(const char *s);

/* ************************************************************************** */
#endif