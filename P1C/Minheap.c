#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

typedef struct cityNode{

char city_name[30];
int aggregated_weight_offered;

}cityNode;

void insert_to_heap(cityNode *city);
cityNode* delete_from_heap();
void heapify_bottom(int index);
void heapify_top(int index);
void displayMinHeap();
void freeHeap();
void updateMinheap(char *cityName, int weight);

cityNode* minheap[100];
int minheapIndex = -1;

int main(){

    int c=1;
    while(c!=0){
       
        scanf("%d",&c);
        cityNode *singlecity = (cityNode*)malloc(sizeof(cityNode));
        singlecity->aggregated_weight_offered = c;
        insert_to_heap(singlecity);

    }

    freeHeap();

return 0;
}

void heapify_bottom(int index){

    cityNode *tempCity;
    int parent;

    while(index != 0){

        parent = (index-1)/2;

        if( minheap[index]->aggregated_weight_offered < minheap[parent]->aggregated_weight_offered ){

            //swap with parent
            tempCity = minheap[parent];
            minheap[parent] = minheap[index];
            minheap[index] = tempCity;
            tempCity = NULL;
            index = parent;

        }
        else{
            break;
        }

    }
}
void heapify_top(int index){

    cityNode *tempCity;
    int leftChild,rightChild;

    while(index <= minheapIndex){

        leftChild = 2*index + 1;
        rightChild = 2*index + 2;

        //only left child case
        if( (leftChild <= minheapIndex) && (rightChild > minheapIndex) && (minheap[index]->aggregated_weight_offered > minheap[leftChild]->aggregated_weight_offered) ){

            //swap with left child 
            tempCity = minheap[index];
            minheap[index] = minheap[leftChild];
            minheap[leftChild] = tempCity;
            tempCity = NULL;
            index = leftChild;

        }
        else if( (leftChild <= minheapIndex) && (rightChild <= minheapIndex) && (minheap[leftChild]->aggregated_weight_offered < minheap[rightChild]->aggregated_weight_offered)  && (minheap[index]->aggregated_weight_offered > minheap[leftChild]->aggregated_weight_offered) ){

            //swap with left child
            tempCity = minheap[index];
            minheap[index] = minheap[leftChild];
            minheap[leftChild] = tempCity;
            tempCity = NULL;
            index = leftChild;

        }
        else if((leftChild <= minheapIndex) && (rightChild <= minheapIndex) && (minheap[rightChild]->aggregated_weight_offered < minheap[leftChild]->aggregated_weight_offered)  && (minheap[index]->aggregated_weight_offered > minheap[rightChild]->aggregated_weight_offered) ){

            //swap with right child
            tempCity = minheap[index];
            minheap[index] = minheap[rightChild];
            minheap[rightChild] = tempCity;
            tempCity = NULL;
            index = rightChild;
        }
        else{
            break;
        }
    }

}

void insert_to_heap(cityNode *city){

    ++minheapIndex;
    minheap[minheapIndex] = city;
    heapify_bottom(minheapIndex);

}
cityNode* delete_from_heap(){

    cityNode *city_to_delete = minheap[0];
    minheap[0] = minheap[minheapIndex];
    minheap[minheapIndex] = NULL;
    minheapIndex--;
    heapify_top(0);

    return city_to_delete;
}

void displayMinHeap(){

    int newline = 2;
    for(int i=0;i<=minheapIndex;++i){

        printf("%d ",minheap[i]->aggregated_weight_offered);

        if(newline-1 == i+1){
            printf("\n");
            newline*=2;
        }

    }
}

void updateMinheap(char *cityName, int weight){

    for(int i=0;i<minheapIndex;++i){
        if(strcmp(minheap[i]->city_name,cityName) == 0){

            minheap[i]->aggregated_weight_offered = weight;
            heapify_bottom(i);
            break;
        }
    }
}


void freeHeap(){

    for(int i=0;i<minheapIndex;++i){
        free(minheap[i]);
        minheap[i] = NULL;
    }

    minheapIndex = -1;
    
}

