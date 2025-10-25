#include <stdio.h>


void bubbleSort(int data[], int n)
{
    int i, j, temp, flag;
    
    flag = 1;
    for(i = 0; i < n - 1 && flag == 1; i++)
    {
        flag = 0;
        for(j = 0; j < n - i - 1; j++)
        {
            if(data[j] > data[j + 1])
            {
                temp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = temp;
                flag = 1;
            }
        }
    }
}


int main()
{
    int raw_data[20], n, i;

    printf("\nEnter the number of elements to be sorted: ");
    scanf("%d", &n);

    printf("\nEnter the elements to be sorted: ");
    for(i = 0; i < n; i++)
    {
        scanf("%d", &raw_data[i]);
    }

    bubbleSort(raw_data, n);

    printf("\nThe sorted elements are:\n");
    for(i = 0; i < n; i++)
    {
        printf("%4d", raw_data[i]);
    }
    printf("\n");

    return 0;
}
