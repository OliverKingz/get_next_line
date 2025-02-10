/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 20:35:18 by ozamora-          #+#    #+#             */
/*   Updated: 2024/11/13 15:34:15 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	ft_lst_tostr(t_list **line, char **line_str, int i_nl);
void	fill_str(t_list **line, char **line_str, int str_len);
void	process_line(int i_nl, t_list **line, char **line_str);
void	read_and_store(int fd, t_list **line);
char	*get_next_line(int fd);

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
void	ft_lst_tostr(t_list **line, char **line_str, int i_nl)
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
void	fill_str(t_list **line, char **line_str, int str_len)
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
void	process_line(int i_nl, t_list **line, char **line_str)
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
void	read_and_store(int fd, t_list **line)
{
	int		bytes_read;
	char	*buffer;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return ;
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return ;
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
	static t_list	*line[MAX_FD];
	char			*line_str;
	int				i_nl;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= MAX_FD)
		return (NULL);
	line_str = NULL;
	read_and_store(fd, &line[fd]);
	if (!line[fd])
		return (NULL);
	i_nl = ft_lst_hasnextline(&line[fd]);
	process_line(i_nl, &line[fd], &line_str);
	if (!line_str || line_str[0] == '\0')
	{
		free(line_str);
		if (!line[fd])
			(ft_lstclear(&line[fd], free), line[fd] = NULL);
		return (NULL);
	}
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
// 	int		fd1;
// 	int		fd2;
// 	int		fd3;
// 	char	*line1;
// 	char	*line2;
// 	char	*line3;

// 	fd1 = open("file0", O_RDONLY);
// 	fd2 = open("file1", O_RDONLY);
// 	fd3 = open("alphabet", O_RDONLY);
// 	if (fd1 == -1 || fd2 == -1 || fd3 == -1)
// 		return (printf("error"), 1);
// 	while (1)
// 	{
// 		line1 = get_next_line(fd1);
// 		line2 = get_next_line(fd2);
// 		line3 = get_next_line(fd3);
// 		(printf("%s", line1), printf("%s", line2), printf("%s", line3));
// 		if (line3 == NULL)
// 			break ;
// 		(free(line1), free(line2), free(line3));
// 	}
// 	(close(fd1), close(fd2), close(fd3));
// 	return (0);
// }
