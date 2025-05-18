#include<stdio.h>
#include<stdbool.h>

bool searchMatrix(int n,int (*mat)[n],int key)
{
    int row = 0;
    int col = n-1;

    while (row<n && col>0)
    {
        if (key == *(*(mat+row)+col) )
        {
            return true;
        }
        else if ( key < *(*(mat+row)+col))
            col--;
        else
            row--;
        
    }
    return false;
    
}

int main()
{
    int n;
    printf("Enter the size of matrix");
    scanf("%d",&n);
    int arr[n][n],key;
    printf("Enter the matrix\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d",&arr[i][j]);
        }
        
    }
    printf("Enter the key");
    scanf("%d",&key);
    if (searchMatrix(n,arr,key))
    {
        printf("element found\n");
    }
    else
    {
        printf("Element not found\n");
    }
    
    return 0;
    
}