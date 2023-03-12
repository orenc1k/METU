#include "the1.h"
#include <climits>

//You can add your own helper functions

int* min_heapify(int array[], int size, int index,long& comparison,long& swap,int* loc_elem[]);
void swap_element(int *p1, int *p2,int** loc_elem);
void insertionSort(int* arr, long &comparison, long & swap, int size) ;
int kWayMergeSortWithHeap(int* arr, int K, int size, long& comparison, long& swap);
void push(int sorted_array[]);
int find_min(int array[],int size);

int find_min(int array[],int size){
  int min=INT_MAX;
  int c, index = 0;
 
  for (c = 0; c < size; c++)
    if (array[c] < min)
      {   min=array[c];
          index = c;
          
      }
  
  return index;  
}

void push(int sorted_array[],int size,int num){
    for (int i=0;i<size;i++){
        if(sorted_array[i]==INT_MIN) {sorted_array[i]=num;
            break;
        }
    }
}



void swap_element(int *p1, int *p2,int** loc_elem)
{
  int temp = *p2;
  *p2 = *p1;
  *p1 = temp;
 
}



void insertionSort(int* arr, long &comparison, long & swap, int size) 
{
    int i,j,temp;
    for (i=1;i<size ; i++){
        
        temp= arr[i];
        j= i-1;
        while (j >=0 && arr[j]>temp){
            
            arr[j+1]=arr[j];
            j--;
            swap++;
            comparison++;
        }
        arr[j+1]=temp;
        comparison++;
    }
    //Your Code Here
}

int* min_heapify(int array[], int size, int index,long& comparison,long& swap,int* loc_elem[])
{
 if (size == 1)
  {
  }
  else
  { int minimum;
    int largest = index;
    int l = 2 * index + 1;
    int r = 2 * index + 2;
    if (l < size )
      { 
          if(array[l] !=INT_MAX && array[largest]!=INT_MAX)
            comparison++;
          if(array[l] < array[largest])
                largest = l;
      }
    if (r < size)
      {  if (array[r]!=INT_MAX && array[largest]!=INT_MAX)
            comparison++;
         if(array[r] < array[largest])
            largest = r;
      }
    if (largest != index)
    {
      swap_element(&array[index], &array[largest],loc_elem);
      if(array[index]!=INT_MAX && array[largest]!=INT_MAX)
        swap++;
      for(int i=size;i>=0;i--)
      min_heapify(array, size, i,comparison,swap,loc_elem);
    }
  }    
  
  return &array[0];
}

int kWayMergeSortWithHeap(int* arr, int K, int size, long& comparison, long& swap){
  int int_max[size];
  int number_of_calls = 1;
  int len;
  int* start=arr; int *loc_elem[K]; 
  int heap[K],sorted_array[size],num_of_elem[K];
	if (size<K) {
	    insertionSort(arr,comparison,swap,size);
	    return number_of_calls;
	}
	
	else{
	    for (len=0;len<K;len++ )
	    {
	        number_of_calls+=kWayMergeSortWithHeap(start,K,size/K,comparison,swap);
	        heap[len]=*start;
	        start+=size/K;
	        
	    }
	}
	start=arr;
	
	for(int i=0; i<K; i++){
	    num_of_elem[i]=(size/K);
	}

	for (int i=0; i<K; i++) {
	loc_elem[i]=start;
	start+=size/K;    
	} start=arr;
	for(int i=0;i<size ;i++ ) sorted_array[i]=INT_MIN;
	for(int i=0;i<size ;i++ ) int_max[i]=INT_MAX;

   for (int m = 0; m <size; m++){
       int* temp;
   
    temp= min_heapify(heap,K,0,comparison,swap,loc_elem); 
    
    push(sorted_array,size,heap[0]);
    
    for (int j=0; j<K; j++){   
        if(*loc_elem[j]==*temp) {
            int val;
            if(num_of_elem[j]>1){ 
                loc_elem[j]++;
                num_of_elem[j]--;
                val=*loc_elem[j];
                swap_element(&val,&heap[0],loc_elem);
                break;
            }   
            else if(num_of_elem[j]==1){
                    
                    *loc_elem[j]=int_max[m];
                    swap_element(&int_max[m],&heap[0],loc_elem);
                break;
                }   
            }
                        
        }
    

    }
   

	/*     for(int i=0;i<K-1;i++){
        int index;
        index=find_min(heap,K);
        sorted_array[size-K+i+1]=heap[index];
        heap[index]=INT_MAX;
    }*/
    
	for (int i=0; i<size;i++)
	    arr[i]=sorted_array[i];
	    

	//Your code here
	return number_of_calls;
}


