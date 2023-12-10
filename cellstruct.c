#include <stdio.h>
#include <stddef.h>
#include <math.h>
#include "cellstruct.h"
t_d_cell *CreateLevelCell(int value, int level)
{
    /// return a pointer to a t_d_cell newcell, with memory allocated for the s_d_cell and the tab of next cells "tabnext"
    /// function takes as parameter an integer value
    /// the level of the cell is the index in the tabnext list
    t_d_cell *newcell;
    newcell = malloc(sizeof(t_d_cell));
    newcell->level = level;
    newcell->value = value;
    newcell->tabnext = malloc(level * sizeof(t_d_cell*));
    for(int i=0; i < level; i++){newcell->tabnext[i]=NULL;}
    return newcell;
}

t_d_list* CreateLevelList(int maxlevel)
{
    /// Returns a pointer to a t_d_list newList, stocking the size of a t_d_list and a tab of heads "tabhead"
    /// It takes as paramter an integer for the maximum level of the level List
    t_d_list *pnlist;
    pnlist = malloc(sizeof(t_d_list));
    pnlist->max_level = maxlevel;
    pnlist->tabhead = malloc(maxlevel * sizeof(t_d_cell*));
    for(int i=0; i < maxlevel; i++){pnlist->tabhead[i]=NULL;}
    return pnlist;
}

t_d_list* CreatePart2List(int n)
{
    ///this function  create the list of the Part 2, it returns a pointer to it
    int NbLevel;
    t_d_list* pnlist = CreateLevelList(n);
    ///We first create a list of level n
    int lenght = ((int)pow(2,n))-1;

    /// we add 2^n-1 level cells to the list, thanks to this for loop
    for(int i=0; i<lenght; i++){
        NbLevel = 0;
        int p=0;
        int x = (int)pow(2,p);
        /// the while loop checks for each cell if its value is divisible by 2^p, p increasing by one every iteration
        ///this allows us to know how much level the current cell will have
        while(((i+1)%x) == 0){
            NbLevel +=1;
            p++;
            x = (int)pow(2,p);
        }
        ///then knowing the value and the level of the cell, we create it and add it to the list
        t_d_cell * pcell = CreateLevelCell(i+1,NbLevel);
        InsertSorted(pnlist, pcell);
    }
    return pnlist;
}

void InsertSorted(t_d_list* plist, t_d_cell* pcell)
{
    ///this function add to the list a cell, in the right place so that the list is in increasing order
    for (int i = 0; i < pcell->level; i++){
        t_d_cell **temp = &(plist->tabhead[i]);
        ///the while loop go through the list until it founds a value greater than the value of the cell
        while (*temp && (*temp)->value < pcell->value) {
            temp = &((*temp)->tabnext[i]);
        }
        ///then it insert the cell at the right place
        pcell->tabnext[i] = *temp;
        *temp = pcell;
    }
}

void AddCellHead(t_d_list* plist, t_d_cell* pcell)
{
    ///this function allows to us to add a cell at the head of the list
    if(pcell->level <= plist->max_level){
        ///replace the head by the new cell, and the new cell next by the previous head
        for (int i = 0; i < pcell->level; i++) {
            t_d_cell *temp = plist->tabhead[i];
            pcell->tabnext[i] = temp;
            plist->tabhead[i] = pcell;
        }
    }
}

void DisplayList(t_d_list* plist)
{
    ///for loop which goes through every row
    for(int i=0; i <= plist->max_level-1; i++){
        ///first display the header
        printf("[list head_%d @-]", i);
        ///initialize pointers to display each row
        t_d_cell* pcell = plist->tabhead[i];
        t_d_cell *temp = plist->tabhead[0];
        ///while loop to display the list until its finished
        while (pcell != NULL){
            ///while loop to offset the display so it is aligned with the list at level 0
            while (pcell->value != temp->value){
                if(pcell->value <= 9){printf("----------");}
                else{if(pcell->value <= 99){printf("---------");}else{printf("--------");}}
                temp = temp->tabnext[0];
            }
            ///display the cell
            printf("-->[ %d|@-]", pcell->value);
            pcell = pcell->tabnext[i];
            temp=temp->tabnext[0];
        }
        ///while loop to display the "NULL" address
        while(temp != NULL){
            if(temp->value <= 9){printf("----------");}
            else{if(temp->value <= 99){printf("---------");}else{printf("--------");}}
            temp = temp->tabnext[0];
        }
        printf("-->NULL\n");
    }
}

t_d_cell *LowSearch(t_d_list* plist, int value)
{
    ///if the head at level 0 is the value we search, return this cell
    t_d_cell* pcell = plist->tabhead[0];
    if(pcell->value == value){return pcell;}
    ///Else we go through the list at level 0 until the value is found.
    while(pcell->tabnext[0]!=NULL){
        if(pcell->value == value){return pcell;}
        pcell = pcell->tabnext[0];
    }/*
    if(found){printf("the value %d is in the list", value);}else{
        printf("the value %d is NOT in the list", value);
    }*/
    return NULL;
}



t_d_cell * BinarySearch(t_d_list *list, int value)
{
    ///Apply binary search to find the value wanted in the list
    ///first we compute the index of the last cell of the array of level
    int level = list->max_level -1 ;
    while(list->tabhead[level] == NULL){
        level--;
    }
    ///then we initialize a "cursor" cell and a cell to keep the previous one.
    t_d_cell *currentcell = list->tabhead[level];
    t_d_cell * prevcell = currentcell ;
    ///loops until all level have been gone through
    while (level >= 0) {
        if (currentcell != NULL) {
            ///if the current cell has the value we search, we return this cell
            if (currentcell->value == value) {
                //printf("Trouver au niveau %d\n", level);
                return currentcell;

            ///binary logic : if the current cell value is lower than the value we search, thanks to the previous cell,
            /// we come back to the previous cell at the level lower
            } else if (currentcell->value < value) {
                prevcell = currentcell;
                currentcell = currentcell->tabnext[level];

            } else {
                level--;
                currentcell = prevcell;
            }
            ///else we come back to the previous cell, but we decrease the level by one more level
        } else if (currentcell == NULL) {
            level--;
            currentcell = prevcell;
        }
    }
    return NULL ;
}

