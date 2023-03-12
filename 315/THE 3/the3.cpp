#include "the3.h"



int recursive_sln(int i, char**& arr, int*& len, int &number_of_calls) { //direct recursive
    number_of_calls+=1;

    //your code here
    char**temp;
    temp=arr;
    
    
    return 0; // this is a dummy return value. YOU SHOULD CHANGE THIS!
}



int memoization_sln(int i, char**& arr, int*& len, int**& mem) { //memoization

int total_length;
    if (i==0){
    char expression=arr[0][1];
    if (expression=='S'){
        total_length=len[0];
        mem[0][0]=0;
        mem[0][1]=0;
        mem[0][2]=total_length;
    }
    else if (expression=='I'){
        total_length=len[0];
        mem[0][0]=total_length;
        mem[0][1]=0;
        mem[0][2]=0;
    }
    else if (expression=='O'){
        total_length=len[0];
        mem[0][0]=0;
        mem[0][1]=total_length;
        mem[0][2]=0;
    }
        return total_length;
    }

    else{
        memoization_sln(i-1,arr,len, mem); 
        char expression_1=arr[i][0], expression_2=arr[i][1];
        switch (expression_2) {
            case 'I':
            if (expression_1=='I'){
                    if(mem[i-1][1]+len[i]>mem[i-1][0])
                        {
                            mem[i][0]=mem[i-1][1]+len[i];
                            mem[i][1]=mem[i-1][1];
                            mem[i][2]=mem[i-1][2];
                        }
                    else{
                        mem[i][0]=mem[i-1][0];
                        mem[i][1]=mem[i-1][1];
                        mem[i][2]=mem[i-1][2];
                    }        
            }

            else if (expression_1=='O'){

                    if(mem[i-1][0]+len[i]>mem[i-1][0]){
                        mem[i][0]=mem[i-1][0]+len[i];
                        mem[i][1]=mem[i-1][1];
                        mem[i][2]=mem[i-1][2];
                    }
                    else{
                        mem[i][0]=mem[i-1][0];
                        mem[i][1]=mem[i-1][1];
                        mem[i][2]=mem[i-1][2];
                    }
            }

            else    if (expression_1=='S'){
                    if(mem[i-1][2]+len[i]>mem[i-1][0]){
                        mem[i][0]=mem[i-1][2]+len[i];
                        mem[i][1]=mem[i-1][1];
                        mem[i][2]=mem[i-1][2];
                    }
                    else{
                        mem[i][0]=mem[i-1][0];
                        mem[i][1]=mem[i-1][1];
                        mem[i][2]=mem[i-1][2];
                    }
            }   
            break;
            case 'O':
   
            if (expression_1=='I'){
                    if(mem[i-1][1]+len[i]>mem[i-1][1]){
                        mem[i][0]=mem[i-1][0];
                        mem[i][1]=mem[i-1][1]+len[i];
                        mem[i][2]=mem[i-1][2];
                    }
                    else{
                        mem[i][0]=mem[i-1][0];
                        mem[i][1]=mem[i-1][1];
                        mem[i][2]=mem[i-1][2];
                    }
                    }
                else if (expression_1=='O'){
                    if(mem[i-1][0]+len[i]>mem[i-1][1]){
                        mem[i][0]=mem[i-1][0];
                        mem[i][1]=mem[i-1][0]+len[i];
                        mem[i][2]=mem[i-1][2];
                    }
                    else{
                        mem[i][0]=mem[i-1][0];
                        mem[i][1]=mem[i-1][1];
                        mem[i][2]=mem[i-1][2];
                    }
                    }
            else if (expression_1=='S'){
                    if(mem[i-1][2]+len[i]>mem[i-1][1]){
                        mem[i][0]=mem[i-1][0];
                        mem[i][1]=mem[i-1][2]+len[i];
                        mem[i][2]=mem[i-1][2];
                        
                    }
                    else{
                        
                        mem[i][0]=mem[i-1][0];
                        mem[i][1]=mem[i-1][1];
                        mem[i][2]=mem[i-1][2];
                    }        
            }
            break;
            case 'S':
            if (expression_1=='I'){
                    if(mem[i-1][1]+len[i]>mem[i-1][2]){
                        mem[i][0]=mem[i-1][0];
                        mem[i][1]=mem[i-1][1];
                        mem[i][2]=mem[i-1][1]+len[i];
                    }
                    else{
                        mem[i][0]=mem[i-1][0];
                        mem[i][1]=mem[i-1][1];
                        mem[i][2]=mem[i-1][2];
                    }
            }
                else if (expression_1=='O'){
                    if(mem[i-1][0]+len[i]>mem[i-1][2]){
                        mem[i][0]=mem[i-1][0];
                        mem[i][1]=mem[i-1][1];
                        mem[i][2]=mem[i-1][0]+len[i];
                    }
                    else{
                        mem[i][0]=mem[i-1][0];
                        mem[i][1]=mem[i-1][1];
                        mem[i][2]=mem[i-1][2];
                    }
                }
            else if (expression_1=='S'){
                    if(mem[i-1][2]+len[i]>mem[i-1][2]){
                        mem[i][0]=mem[i-1][0];
                        mem[i][1]=mem[i-1][1];
                        mem[i][2]=mem[i-1][2]+len[i];
                    }
                    else{
                        mem[i][0]=mem[i-1][0];
                        mem[i][1]=mem[i-1][1];
                        mem[i][2]=mem[i-1][2];
                    }
            }
            break;
        }           
    
        return total_length;
    }
        
}


int dp_sln(int size, char**& arr, int*& len, int**& mem) { 
   int total_length; 
    char expression=arr[0][1];
    if (expression=='S'){
        total_length=len[0];
        mem[0][0]=0;
        mem[0][1]=0;
        mem[0][2]=total_length;
    }
    else if (expression=='I'){
        total_length=len[0];
        mem[0][0]=total_length;
        mem[0][1]=0;
        mem[0][2]=0;
    }
    else if (expression=='O'){
        total_length=len[0];
        mem[0][0]=0;
        mem[0][1]=total_length;
        mem[0][2]=0;
    }
    for(int i=1; i<size; i++) {
        char expression_1=arr[i][0], expression_2=arr[i][1];
        switch (expression_2) {
            case 'I':
            if (expression_1=='I'){
            
                    if(mem[i-1][1]+len[i]>mem[i-1][0])
                        {
                            mem[i][0]=mem[i-1][1]+len[i];
                            mem[i][1]=mem[i-1][1];
                            mem[i][2]=mem[i-1][2];
                        }
                    else{
                        mem[i][0]=mem[i-1][0];
                        mem[i][1]=mem[i-1][1];
                        mem[i][2]=mem[i-1][2];
                    }        
            }

            else if (expression_1=='O'){

                    if(mem[i-1][0]+len[i]>mem[i-1][0]){
                        mem[i][0]=mem[i-1][0]+len[i];
                        mem[i][1]=mem[i-1][1];
                        mem[i][2]=mem[i-1][2];
                    }
                    else{
                        mem[i][0]=mem[i-1][0];
                        mem[i][1]=mem[i-1][1];
                        mem[i][2]=mem[i-1][2];
                    }
            }

            else    if (expression_1=='S'){
                    if(mem[i-1][2]+len[i]>mem[i-1][0]){
                        mem[i][0]=mem[i-1][2]+len[i];
                        mem[i][1]=mem[i-1][1];
                        mem[i][2]=mem[i-1][2];
                    }
                    else{
                        mem[i][0]=mem[i-1][0];
                        mem[i][1]=mem[i-1][1];
                        mem[i][2]=mem[i-1][2];
                    }
            }   
            break;
            case 'O':
   
            if (expression_1=='I'){
                    if(mem[i-1][1]+len[i]>mem[i-1][1]){
                        mem[i][0]=mem[i-1][0];
                        mem[i][1]=mem[i-1][1]+len[i];
                        mem[i][2]=mem[i-1][2];
                    }
                    else{
                        mem[i][0]=mem[i-1][0];
                        mem[i][1]=mem[i-1][1];
                        mem[i][2]=mem[i-1][2];
                    }
                    }
                else if (expression_1=='O'){
                    if(mem[i-1][0]+len[i]>mem[i-1][1]){
                        mem[i][0]=mem[i-1][0];
                        mem[i][1]=mem[i-1][0]+len[i];
                        mem[i][2]=mem[i-1][2];
                    }
                    else{
                        mem[i][0]=mem[i-1][0];
                        mem[i][1]=mem[i-1][1];
                        mem[i][2]=mem[i-1][2];
                    }
                    }
            else if (expression_1=='S'){
                    if(mem[i-1][2]+len[i]>mem[i-1][1]){
                        mem[i][0]=mem[i-1][0];
                        mem[i][1]=mem[i-1][2]+len[i];
                        mem[i][2]=mem[i-1][2];
                        
                    }
                    else{
                        
                        mem[i][0]=mem[i-1][0];
                        mem[i][1]=mem[i-1][1];
                        mem[i][2]=mem[i-1][2];
                    }        
            }
            break;
            case 'S':
            if (expression_1=='I'){
                    if(mem[i-1][1]+len[i]>mem[i-1][2]){
                        mem[i][0]=mem[i-1][0];
                        mem[i][1]=mem[i-1][1];
                        mem[i][2]=mem[i-1][1]+len[i];
                    }
                    else{
                        mem[i][0]=mem[i-1][0];
                        mem[i][1]=mem[i-1][1];
                        mem[i][2]=mem[i-1][2];
                    }
            }
                else if (expression_1=='O'){
                    if(mem[i-1][0]+len[i]>mem[i-1][2]){
                        mem[i][0]=mem[i-1][0];
                        mem[i][1]=mem[i-1][1];
                        mem[i][2]=mem[i-1][0]+len[i];
                    }
                    else{
                        mem[i][0]=mem[i-1][0];
                        mem[i][1]=mem[i-1][1];
                        mem[i][2]=mem[i-1][2];
                    }
                }
            else if (expression_1=='S'){
                    if(mem[i-1][2]+len[i]>mem[i-1][2]){
                        mem[i][0]=mem[i-1][0];
                        mem[i][1]=mem[i-1][1];
                        mem[i][2]=mem[i-1][2]+len[i];
                    }
                    else{
                        mem[i][0]=mem[i-1][0];
                        mem[i][1]=mem[i-1][1];
                        mem[i][2]=mem[i-1][2];
                    }
            }
            break;
        }   

    }


    
    for (int i=0;i<3;i++)
        {
            if (mem[size-1][i]>total_length) total_length=mem[size-1][i];
        }
    return total_length; // this is a dummy return value. YOU SHOULD CHANGE THIS!
}
