/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:28:58 by ozamora-          #+#    #+#             */
/*   Updated: 2025/02/10 22:59:33 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	ft_lst_tostr(t_list **line, char **line_str, int i_nl);
static void	fill_str(t_list **line, char **line_str, int str_len);
static void	process_line(int i_nl, t_list **line, char **line_str);
static void	read_and_store(int fd, t_list **line);
char		*get_next_line(int fd);

/**
 * ft_lst_tostr - Converts list content to a string.
 * @param line: A pointer to the list containing the data.
 * @param line_str: A pointer to the string that will hold the combined content.
 * @param i_nl: The position of the newline character.
 * 
 * Return: 
 *  - No return value.
 * Description:
 *  - Calculates the total length of the string based on list content.
 *  - Allocates memory for the resulting string.
 *  - Fills the string with characters from the list until the newline or end.
 */
static void	ft_lst_tostr(t_list **line, char **line_str, int i_nl)
{
	int		str_len;
	t_list	*current;

	if (!line || !(*line))
		return ;
	if (i_nl < 0)
	{
		current = *line;
		str_len = 0;
		while (current)
		{
			str_len += ft_strlen(current->content);
			current = current->next;
		}
	}
	else
		str_len = i_nl + 1;
	*line_str = (char *)malloc((str_len + 1) * sizeof(char));
	if (!(*line_str))
	{
		free(*line_str);
		*line_str = NULL;
		return ;
	}
	fill_str(line, line_str, str_len);
}

/**
 * fill_str - Fills a string with content from the list.
 * @param line: A pointer to the list containing the data.
 * @param line_str: A pointer to the string to fill.
 * @param str_len: The length of the string to fill.
 * 
 * Return: 
 *  - No return value.
 * Description:
 *  - Iterates through the list and fills the string with characters.
 *  - Handles the inclusion of the newline character as needed.
 */
static void	fill_str(t_list **line, char **line_str, int str_len)
{
	int		i;
	int		j;
	t_list	*current;

	current = *line;
	i = 0;
	while (current != NULL && i < str_len)
	{
		j = 0;
		while (((char *)current->content)[j] && i < str_len)
			(*line_str)[i++] = ((char *)current->content)[j++];
		current = current->next;
	}
	(*line_str)[str_len] = '\0';
}

/**
 * process_line - Processes the contents of the list based on newline position.
 * @param i_nl: Index of the newline character in the list.
 * @param line: A pointer to the list containing the read data.
 * @param line_str: A pointer to the string that will hold the processed line.
 * 
 * Return: 
 *  - No return value.
 * Description:
 *  - Converts list content into a string if a newline or EOF is encountered.
 *  - Clears the list after processing and updates it based on remaining 
 *    content.
 */
static void	process_line(int i_nl, t_list **line, char **line_str)
{
	t_list	*new;
	t_list	*last;
	char	*content_til_nl;

	if (i_nl < 0)
	{
		ft_lst_tostr(line, line_str, i_nl);
		ft_lstclear(line, free);
		*line = NULL;
	}
	else
	{
		new = NULL;
		last = ft_lstlast(*line);
		ft_lst_tostr(line, line_str, i_nl);
		content_til_nl = (char *)last->content;
		while (*content_til_nl != '\0' && *content_til_nl != '\n')
			content_til_nl++;
		if (*content_til_nl == '\n')
			content_til_nl++;
		if (*content_til_nl)
			ft_lst_new_addback(content_til_nl, &new, ft_strlen(content_til_nl));
		ft_lstclear(line, free);
		*line = new;
	}
}

/**
 * read_and_store - Reads data from the file descriptor into a list.
 * @param fd: The file descriptor to read from.
 * @param line: A pointer to the list to store read data.
 * 
 * Return: 
 *  - No return value.
 * Description:
 *  - Allocates a buffer and reads from the fd in a loop.
 *  - Stores the read data in the list until a newline is found or EOF is 
 *    reached.
 *  - Frees the buffer after reading.
 */
static void	read_and_store(int fd, t_list **line)
{
	int		bytes_read;
	char	*buffer;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return ;
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (ft_lstclear(line, free), line = NULL, free(buffer));
	bytes_read = 1;
	while (bytes_read != 0 && (ft_lst_hasnextline(line) < 0))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == 0)
			return (free(buffer));
		if (bytes_read == -1)
			return (ft_lstclear(line, free), line = NULL, free(buffer));
		buffer[bytes_read] = '\0';
		ft_lst_new_addback(buffer, line, bytes_read);
	}
	free(buffer);
}

/**
 * get_next_line - Reads the next line from a file descriptor.
 * @param fd: The file descriptor from which to read.
 * 
 * Return: 
 *  - A pointer to the line read from the file descriptor,
 *  - NULL if there are no more lines to read or an error occurs.
 * Description:
 *  - Manages the process of reading and returning the next line from the fd.
 *  - Calls read_and_store to read data into a list until a newline or EOF is 
 *    found.
 *  - Uses process_line to convert the list's content into a string for return.
 */
char	*get_next_line(int fd)
{
	static t_list	*line;
	char			*line_str;
	int				i_nl;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line_str = NULL;
	read_and_store(fd, &line);
	if (!line)
		return (NULL);
	i_nl = ft_lst_hasnextline(&line);
	process_line(i_nl, &line, &line_str);
	if (!line_str)
		return (NULL);
	return (line_str);
}

/* ************************************************************************** */
/* ************************* UNCOMMENT FOR TESTING  ************************* */
/* ************************************************************************** */

// void	ft_lstprint(t_list *line)
// {
// 	t_list	*current;

// 	current = line;
// 	while (current)
// 	{
// 		printf("(%s)-> ", (char *)(current->content));
// 		current = current->next;
// 	}
// 	printf("(NULL)\n");
// }

// int	main(void)
// {
// 	int		fd;
// 	char	*line;

// 	fd = open("file0", O_RDONLY);
// 	if (fd == -1)
// 		return (printf("error"), 1);
// 	while (1)
// 	{
// 		line = get_next_line(fd);
// 		printf("%s", line);
// 		if (line == NULL)
// 			break ;
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }
