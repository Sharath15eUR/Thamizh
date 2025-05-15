#include<stdio.h>
#include<string.h>

#define TOT_DAYS 7
#define MAX_TASKS 3
#define MAX_TASK_LENGTH 50

struct Day
{
    char dayName[10];
    char tasks[MAX_TASKS][MAX_TASK_LENGTH];
    int taskCount;
};

void addTasks(struct Day week[])
{
    char dayInput[10];
    int taskIndex;

    printf("Enter the day to add tasks: ");
    scanf("%s",dayInput);

    for (int i = 0; i < TOT_DAYS; i++)
    {
        if (strcasecmp(week[i].dayName,dayInput) == 0)
        {
            if (week[i].taskCount >= MAX_TASKS)
            {
                printf("no more tasks can be added for %s\n",week[i].dayName);
                return;
            }

            int rem_tasks=MAX_TASKS-week[i].taskCount;
            printf("You can add %d tasks\n",rem_tasks);

            printf("Enter the task %d for %s",week[i].taskCount+1,week[i].dayName);
            scanf(" %[^\n]",week[i].tasks[week[i].taskCount]);
            return;
        }
        
    }
    printf("invalid day name");
}

void displayTasks(struct Day week[])
{
    for (int i = 0; i < TOT_DAYS;  i++)
    {
        printf("Day: %s",week[i].dayName);
        if (week[i].taskCount>0)
        {
            for (int j = 0; j < week[i].taskCount; j++)
            {
                printf("- %s\n",week[i].tasks[j]);
            }
            
        }
        else    
            printf("No tasks found");
        
        
    }
    
}

int main()
{
    struct Day week[]=
    {
        {"Monday",{},0},
        {"Tuesday",{},0},
        {"Wednesday",{},0},
        {"Thursday",{},0},
        {"Friday",{},0},
        {"Saturday",{},0},
        {"Sunday",{},0},
    };
    int choice;
    do
    {
        printf("the choices are: \n");
        printf("1. add tasks \n");
        printf("2. display tasks \n");
        printf("3. exit");
        scanf("%d",&choice);

        switch (choice)
        {
        case 1:
            addTasks(week);
            break;
        case 2:
            displayTasks(week);
            break;
        case 3:
            printf("good bye");
            break;
        
        default:
            printf("Invalid option");
        }

    } while (choice !=3);
    return 0;
}