#include <stdio.h>
#include<stdlib.h>
int main()
{
    
    int i ,min, count = 0;;
    int *array;
    int n;
    printf("\n\nCount total number of duplicate elements in an array:\n");
    printf("---------------------------------------------------------\n");	
    printf("Input the number of elements to be stored in the array :");
    scanf("%d",&n);	
    array = (int*)malloc(n*sizeof(int));
	
    printf("Input %d elements in the array :\n",n);
    for(i=0;i<n;i++)
        {
	      printf("element - %d : ",i);
	      scanf("%d",&array[i]);
	    }

/*----------------- sort array ------------------------------------*/   
for(int j = 0; j < n - 1; j++)
    {
        for(int k = j + 1;k < n;k++)
        {
            if(array[j] < array[k])
            {
            int temp = array[j];
            array[j] = array[k];
            array[k] = temp;   
            }
        }
        
    }

/*------------------- print sorted array -------------------------*/
printf("the sorted array is \n");
for(i = 0; i < n; i++)   
printf("%d ", array[i]);

/*------------------- count duplicate -------------------------*/
for(i=1;i<n;i++)
    {
        if(array[i]==array[i-1])
        {
            count++;
            while(array[i]==array[i-1]) i++;
        }
    }

    printf("The total number of duplicate elements found in the array is: %d \n", count);
    
	printf("\n\n");

    return 0;
 		
}