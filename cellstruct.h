#include <stdio.h>
#include <stdlib.h>

typedef struct s_d_cell
{
    int value;
    int level;
    struct s_d_cell **tabnext;
} t_d_cell;

typedef struct s_d_list
{
    int max_level;
    struct s_d_cell **tabhead;
} t_d_list;


t_d_cell* CreateLevelCell(int value, int level);

t_d_list* CreateLevelList(int maxlevel);
t_d_list* CreatePart2List(int n);


void AddCellHead(t_d_list *, t_d_cell*);
void InsertSorted(t_d_list*, t_d_cell*);
void DisplayList(t_d_list*);

t_d_cell *LowSearch(t_d_list*, int);
t_d_cell* BinarySearch(t_d_list*, int);