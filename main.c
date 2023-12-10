#include "cellstruct.h"
#include <stdio.h>
#include <stdlib.h>
#include "timer.h"
#include "math.h"

int main()
{
/*
    ///part 1
    t_d_list * plist = CreateLevelList( 5);
        ///cells
        t_d_cell * pcell1 = CreateLevelCell(1,5);
        t_d_cell * pcell2 = CreateLevelCell(2,3);
        t_d_cell * pcell3 = CreateLevelCell(3,1);
        t_d_cell * pcell4 = CreateLevelCell(4,2);
        t_d_cell * pcell5 = CreateLevelCell(5,4);

    AddCellHead(plist, pcell1);
    InsertSorted(plist, pcell3);
    InsertSorted(plist, pcell4);
    InsertSorted(plist, pcell5);
    InsertSorted(plist, pcell2);

    DisplayList(plist);
*/
    ///part2
    t_d_list * plist = CreatePart2List(3);
    DisplayList(plist);

    LowSearch(plist, 5);
    BinarySearch(plist, 5);

/*
    ///complexity

    FILE * log_file = fopen("log.txt", "w+");
    if(log_file != NULL){printf("open");}

    char format[] = "%d\t%s\t%s\n" ;
    int level;
    char *time_lvl0;
    char *time_all_levels;
    t_timer timer;

    level = 7;
    int NbrSearch = 100000;
    while(level <= 15){
        t_d_list* plist = CreatePart2List(level);

        srand(time(NULL));
        int range = (int)pow(2,level)-1;
        int min = 1;

        startTimer();
        for (int i=0; i<NbrSearch; i++){
            int randint = rand() % range + min;
            LowSearch(plist, randint);
        }
        stopTimer();
        time_lvl0 = getTimeAsString();

        startTimer();
        for (int i=0; i<NbrSearch; i++){
            int randint = rand() % range + min;
            BinarySearch(plist, randint);
        }
        stopTimer();
        time_all_levels = getTimeAsString();

        fprintf(stdout, format, level, time_lvl0, time_all_levels);

        level++;
        free(plist);

    }
    fclose(log_file);
*/
    return 0;
}
