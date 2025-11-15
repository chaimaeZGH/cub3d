/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czghoumi <czghoumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 23:09:01 by czghoumi          #+#    #+#             */
/*   Updated: 2025/11/15 08:20:01 by czghoumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3D.h"

bool chck_cub(char *arg)
{
    int i = 0;
    while(arg[i]!='\0')
    {
        if(arg[i]==' ')
            return false;
        i++;
    }
    int a = ft_strncmp(&arg[i-4], ".cub", 4);
    if(a == 0)
        return true;
    else
        return false;
}

int	ft_count(char const *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
			i++;
		if (s[i] != '\0')
			j++;
		while ((s[i] != ' ' || s[i] == '\t' || s[i] == '\n')&& s[i] != '\0')
			i++;
	}
	return (j);
}

int   chack_empty_line(char *line)
{
    int i = 0;
    while(line[i] != '\0')
    {
        if(line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
            i++;
        else
            return (0);
    }
    return (1);
}
void    free_mymap(t_pars *my_map)
{
    int i = 0;
    if(my_map == NULL)
        return;
    if(my_map->no != NULL)
        free(my_map->no);
    if(my_map->so != NULL)
        free(my_map->so);
    if(my_map->we != NULL)
        free(my_map->we);
    if(my_map->ea != NULL)
        free(my_map->ea);
    if(my_map->ceil != NULL)
        free(my_map->ceil);
    if(my_map->floor != NULL)
        free(my_map->floor);
    if(my_map->map!=NULL)
    {
        while(my_map->map[i]!=NULL)
            free(my_map->map[i++]);   
        free(my_map->map);
    }
    free(my_map);
}

char *firs_word(char *line)
{
    int i;
    int length;
    int start;

    i = 0;
    length = 0;
    while(line[i] == ' ' || line[i] == '\t' )
        i++;
    start = i;
    while (line[i] != ' ' && line[i] != '\t' && line[i] != '\0' && line[i] != '\n')
    {
        length++;
        i++;
    }
    char *word = malloc(length + 1);
    if (!word) 
        return NULL;
    int j = 0;
    while (j < length)
    {
        word[j] = line[start + j];
        j++;
    }
    word[length] = '\0';
    return word;
}

char *last_word(char *line)
{
    int i;
    int length;
    int start;

    if (!line)
        return NULL;
    i = 0;
    while (line[i] != '\0')
        i++;
    i--;
    while (i >= 0 && (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'))
        i--;
    if (i < 0)
        return NULL;
    length = 0;
    start = i;
    while (i >= 0 && line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
    {
        length++;
        i--;
    }
    start = i + 1;
    char *word = malloc(length + 1);
    if (!word) 
        return NULL;
    int j = 0;
    while (j < length)
    {
        word[j] = line[start + j];
        j++;
    }
    word[length] = '\0';
    return word;
}

int	cub_atoi(const char *str)
{
	int	result;
	int	i;

	i = 0;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
    if(i > 0)
        return (-1);
	if (str[i] == '-' || str[i] == '+') 
	{
		if (str[i] == '-')
			return(-1);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9') 
	{
		result = (result * 10) + (str[i] - '0');
		if (result > 255)
			return (-1);
		i++;
	}
    if(str[i]!='\0')
        return(-1);
	return (result);
}

rgb_t   *colors_parce(char *word)
{
    char **rgb;
    rgb = ft_split(word,',');
    if(!rgb)
        return (NULL);
    int j = 0;
    while(rgb[j]!=NULL)
        j++;
    int i = 0;
    if(j != 3)
    {
        while(rgb[i]!=NULL)
        {
            free(rgb[i]);
            i++;
        }
        free(rgb);
            return NULL;
    }
    rgb_t *color;
    color = malloc(sizeof(rgb_t));
    i = 0;
    while(rgb[i] != NULL)
    {
        if(cub_atoi(rgb[i]) == -1 )
        {
            i = 0;
            while(rgb[i]!= NULL)
            {
                free(rgb[i]);
                i++;
            }
            free(rgb);
            free(color);
            return NULL;
        }
        i++;
    }
    color->r = cub_atoi(rgb[0]);
    color->g = cub_atoi(rgb[1]);
    color->b = cub_atoi(rgb[2]);
    free(word);
    i = 0;
    while(rgb[i]!=NULL)
    {
        free(rgb[i]);
        i++;
    }
    free(rgb);
    return(color);
}

char *trim_line(char *line)
{
    int i;

    if (!line)
        return NULL;
    i = 0;
    while (line[i] != '\0')
        i++;
    i--;
    while (i >= 0 && (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'))
        i--;
    if (i < 0)
        return NULL;
    char *new_line=malloc(i+2);
    if (!new_line)
        return NULL;
    int j = 0;
    while(j<=i)
    {   
        new_line[j]=line[j];
        j++;
    }
    new_line[j]='\0';
    return (new_line);
}
int    fill_mapst(char *line,t_pars *my_map)
{
    char    *word;
    char    *last;
    if(line == NULL)
        return 2;
    word = firs_word(line);
    if(ft_strncmp(word, "NO", 2)== 0 && ft_strlen(word)==ft_strlen("NO"))
    {
        free(word);
        int s = ft_count(line);
        if(s != 2)
        {
            free_mymap(my_map);
            return (0);
        }
        last = last_word(line);
        if(my_map->no == NULL)
            my_map->no = last;
        else
        {
            free(last);
            free_mymap(my_map);
            return (0);
        }
    }
    else if(ft_strlen(word)==ft_strlen("SO") && ft_strncmp(word, "SO", 2)== 0)
    {
        free(word);
        int s = ft_count(line);
        if(s != 2)
        {
            free_mymap(my_map);
            return (0);
        }
        last = last_word(line);
        if(my_map->so == NULL)
            my_map->so = last;
        else
        {
            free(last);
            free_mymap(my_map);
            return (0);
        }
    }
    else if(ft_strlen(word)==ft_strlen("EA") && ft_strncmp(word, "EA", 2)== 0)
    {
        free(word);
        int s = ft_count(line);
        if(s != 2)
        {
            free_mymap(my_map);
            return (0);
        }
        last = last_word(line);
        if(my_map->ea == NULL)
            my_map->ea = last;
        else
        {
            free(last);
            free_mymap(my_map);
            return (0);
        }
    }
    else if(ft_strlen(word)==ft_strlen("WE") && ft_strncmp(word, "WE", 2)== 0)
    {
        free(word);
        int s = ft_count(line);
        if(s != 2)
        {
            free_mymap(my_map);
            return (0);
        }
        last = last_word(line);
        if(my_map->we == NULL)
            my_map->we = last;
        else
        {
            free(last);
            free_mymap(my_map);
            return (0);
        }
    }
    else if(ft_strlen(word)==ft_strlen("F") && ft_strncmp(word, "F", 1)== 0)
    {
        free(word);
        int s = ft_count(line);
        if(s != 2)
        {
            free_mymap(my_map);
            return (0);
        }
        last = last_word(line);
        if(my_map->floor == NULL)
        {
            my_map->floor = colors_parce(last);
            if(my_map->floor  == NULL)
            {
                free(last);
                free_mymap(my_map);
                return (0);
            }
        }
        else
        {
            free(last);
            free_mymap(my_map);
            return (0);
        }
    }
    else if(ft_strlen(word) == ft_strlen("C") && ft_strncmp(word, "C", 1) == 0)
    {
        free(word);
        int s = ft_count(line);
        if(s != 2)
        {
            free_mymap(my_map);
            return (0);
        }
        last = last_word(line);
        if(my_map->ceil == NULL)
        {
            my_map->ceil = colors_parce(last);
            if(my_map->ceil == NULL)
            {
                free_mymap(my_map);
                return (0);
            }
        }
        else
        {
            free(last);
            free_mymap(my_map);
            return (0);
        }
    }
    else if (my_map->no != NULL && my_map->so != NULL && my_map->ea!=NULL && my_map->we!=NULL && my_map->floor!=NULL && my_map->ceil!=NULL && word[0] == '1' && my_map->stop == false)
    {
        free(word);
        if (my_map->map == NULL)
        {
            my_map->map = malloc(sizeof(char *) * 2);
            if(!my_map->map)
                return 0;
            my_map->map[0] = trim_line(line);
            my_map->map[1] = NULL;
        }
        else 
        {
            int s = 0;
            while(my_map->map[s] != NULL)
                s++;
            char **new_map = malloc((s + 2) * sizeof(char *));
            if (!new_map)
                return 0;
            int i = 0;
            while (i < s) 
            {
                new_map[i] = my_map->map[i];
                i++;
            }
            new_map[s] = trim_line(line);
            if (!new_map[s]) 
            {
                free(new_map);
                return 0;
            }
            new_map[s + 1] = NULL;
            free(my_map->map);
            my_map->map = new_map;
        }
    }
    else
    {
        printf("%s ok haa\n",word);
        free(word);
        free_mymap(my_map);
        return (0);
    }
    return (1);
}

void ll()
{
    system ("leaks cub3D");
}

bool    check_content(char *line)
{
    int i = 0;
    
    while(line[i]!='\0')
    {
        if(!(line[i]== ' ' ||line[i]== '\t'|| line[i]== '\n'  || line[i] == '0' || line[i] == '1' || line[i] == 'N'|| line[i] == 'S' || line[i] == 'E' ||line[i] == 'W'))
            return false; 
        i++;
    }
    if(line[i-1] != '1')
        return false;
    return true;
}

bool check_line(char *line)
{
     int i = 0;
    while(line[i]!='\0')
    {
        if(!(line[i]== ' ' ||line[i]== '\t' ||line[i]== '1'||line[i]== '\n'))
            return false;
        i++;
    }
    return true;
}

bool check_zero_pos(char **map)
{
    int i = 1;
    int j;
    if (!map || !map[0]) 
        return false;
    while(map[i+1] != NULL)
    {
        j = 1;
        while(map[i][j+1] != '\0')
        {
            if(map[i][j] == '0')
            {
                if(j >= (int)ft_strlen(map[i-1]) || map[i-1][j] == ' ')
                    return false;
                if(j >= (int)ft_strlen(map[i+1]) || map[i+1][j] == ' ')
                    return false;
                if(map[i][j-1] == ' ')
                    return false;
                if(map[i][j+1] == ' ')
                    return false;
            }
            j++;
        }
        i++;
    }
    return true;
}

int check_map(char **map)
{
    // ther is 1 0 (N/S/E/W) SPACE
    if(!map)
        return 0;
    int i = 0;
    
    while(map[i] != NULL)
    {
        if(check_content(map[i]) == false)
            return 0;
        i++;
    }
    if(check_line(map[0]) == false || check_line(map[i-1]) == false)
        return 0;
    if(check_zero_pos(map) == false)
        return 0;
    return 1;
}

int main(int argc, char **argv)
{
    if(argc < 2 || argc > 4)
        return(printf("erreur in args\n"),1);
    if(ft_count(argv[1]) > 1)
        return(printf("erreur in file name\n"),1);
    if(!chck_cub(argv[1]))
        return(printf("erreur in file name only '*.cub'\n"),1);
    int s = open(argv[1],O_RDONLY);
    if(s < 0)
        return (printf("erreur in oprning file\n"),1);
    printf("-->%d\n",s);
    t_pars *my_map;
    my_map = malloc(sizeof(t_pars));
    my_map->ea = NULL;
    my_map->no = NULL;
    my_map->so = NULL;
    my_map->we = NULL;
    my_map->map = NULL;
    my_map->stop = false;
    char *line;
    line = get_next_line(s);
    while(line != NULL)
    {
        while(line != NULL && chack_empty_line(line) == 1)
        {
            free(line);
            if(my_map!=NULL && my_map->map!=NULL)
                my_map->stop = true;
            line = get_next_line(s);
        }
        if(fill_mapst(line,my_map) == 0)
        {
            free(line);
            printf("erreur in map\n");
            // atexit(ll);
            return (1);
        }
        free(line);
        line = get_next_line(s);
    }
    free(line);
    
    if(check_map(my_map->map) == 0)
    {
        printf("map form is not corect\n");
        free_mymap(my_map);
        my_map = NULL; 
    }
    printf("done\n");
    if(my_map!=NULL)
        free_mymap(my_map);
    // atexit(ll);
}