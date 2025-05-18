#include<stdio.h>

void reArrange(int *arr, int size)
{
    int *right = arr+size;
    int *left = arr;

    while (left<right)
    {
        if(*left%2 == 0)
        {
            left++;
            continue;
        }
        int *pointer = left+1;

        while (pointer<right && (*pointer%2!=0))
        {
            pointer++;
        }

        if (pointer==right)
        {
            break;
        }

        int nextEven = *pointer;
        int *shift = pointer;

        while (shift>left)
        {
            *shift = *(shift-1);
            shift--;
        }

        *left = nextEven;
        left++;
        
        
    }

}

void printArray(int *arr, int size)
{
    for (int *ptr = arr; ptr <arr+size; ptr++)
    {
        printf("%d ",*ptr);
    }
    printf("\n");
}

int main()
{
    printf("Enter the size");
    int size;
    scanf("%d",&size);
    int arr[size];

    for (int i = 0; i < size; i++)
    {
        scanf("%d",(arr+i));
    }
    printf("original array \n");
    printArray(arr,size);
    printf("Modified array\n");
    reArrange(arr,size);
    printArray(arr,size);
    return 0;   
}