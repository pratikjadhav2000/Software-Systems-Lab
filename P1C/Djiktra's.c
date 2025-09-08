#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#define INF 99999

//structure definitions

//graph
typedef struct adjacentNode{

char city_name[30];
int weight;
struct adjacentNode *next;

}adjacentNode;

typedef struct vertex{

char city_name[30];
adjacentNode *adjacencyFirst,*adjacencyLast;
struct vertex *next;

}Vertex;

//heap
typedef struct cityNode{

char city_name[30];
int aggregated_weight_offered;

}cityNode;


//global variable declarations

//graph
Vertex *firstVertex = NULL;
Vertex *lastVertex = NULL;

//heap
cityNode* minheap[100];
int minheapIndex = -1;

//function declarations

//graph
void addVertex(char *source,char *destination);
int findShortestDistance(char *source,char *destination);
void freeGraph();

//heap 
void insert_to_heap(cityNode *city);
cityNode* delete_from_heap();
void heapify_bottom(int index);
void heapify_top(int index);
void displayMinHeap();
void freeHeap();
void updateMinheap(char *cityName, int weight);

int main(){


  //get count of total cities
  int numberOfCities, arrayPlace;
  char inputChar;
  char totalcities[20];
  arrayPlace = 0;
  while((inputChar = getchar()) != '\n'){
    totalcities[arrayPlace++] = inputChar;
  }
  totalcities[arrayPlace] = '\0';
  numberOfCities = atoi(totalcities);

  for(int i=0;i<numberOfCities;++i){

      // get source_city_name
      char source_city_name[30];
      arrayPlace = 0;
      while ((inputChar = getchar()) != ',')
      {
        source_city_name[arrayPlace++] = inputChar;
      }
      source_city_name[arrayPlace] = '\0';
      // printf("%s ",source_city_name);

      // get destination_city_name
      arrayPlace = 0;
      char destination_city_name[30];
      while ((inputChar = getchar()) != '\n')
      {
        destination_city_name[arrayPlace++] = inputChar;
      }
      destination_city_name[arrayPlace] = '\0';
  
      //adding vertex call add function 2 times -> add(source,destination) & add(destination,source)
      addVertex(source_city_name,destination_city_name);
      addVertex(destination_city_name,source_city_name);

    }

    //print vertices
    /*
    printf("\n************\n");
    Vertex *vertexScanner = firstVertex;
    while(vertexScanner!=NULL){
        printf("%s -> ",vertexScanner->city_name);

        adjacentNode *adjacentNodeScanner = vertexScanner->adjacencyFirst;
        while(adjacentNodeScanner!=NULL){
            printf("%s, ",adjacentNodeScanner->city_name);
            adjacentNodeScanner = adjacentNodeScanner->next; 
        }
        printf("\n");
        vertexScanner = vertexScanner->next;
    }
    printf("\n************\n");
    */

    
    int shortestDistance = 0;
    shortestDistance = findShortestDistance("Kasaragode", "Kozhikode");
    printf("%d\n",shortestDistance);

freeGraph();
return 0;  
}

//function definitions

//graph
void addVertex(char *source, char *destination)
{

    // create Vertex
    Vertex *singleVertex = (Vertex *)malloc(sizeof(Vertex));
    strcpy(singleVertex->city_name, source);
    singleVertex->adjacencyFirst = NULL;
    singleVertex->adjacencyLast = NULL;
    singleVertex->next = NULL;

    // create Ajacent node
    adjacentNode *singleadjacent = (adjacentNode *)malloc(sizeof(adjacentNode));
    strcpy(singleadjacent->city_name, destination);
    singleadjacent->weight = 1;
    singleadjacent->next = NULL;

    // add source as vertex to list
    if (firstVertex == NULL)
    {
        firstVertex = singleVertex;
        lastVertex = singleVertex;
    }
    else
    {

        // check if vertex already exist in vertex list
        Vertex *vertexScanner = firstVertex;
        bool vertexExist = false;
        while (vertexScanner != NULL)
        {
            if (strcmp(vertexScanner->city_name, source) == 0)
            {
                vertexExist = true;
                free(singleVertex);
                singleVertex = vertexScanner;
                break;
            }

            vertexScanner = vertexScanner->next;
        }
        // add if not exist in vertex list
        if (!vertexExist)
        {

            lastVertex->next = singleVertex;
            lastVertex = singleVertex;
        }
    }

    // add destination to adjacency list
    if (singleVertex->adjacencyFirst == NULL)
    {
        singleVertex->adjacencyFirst = singleadjacent;
        singleVertex->adjacencyLast = singleadjacent;
    }
    else
    {

        // check if adjacent already exist in adjacent list
        adjacentNode *adjacentListScanner = singleVertex->adjacencyFirst;
        bool vertexAdjacentExist = false;

        while (adjacentListScanner != NULL)
        {
            if (strcmp(adjacentListScanner->city_name, destination) == 0)
            {
                vertexAdjacentExist = true;
                free(singleadjacent);
                break;
            }

            adjacentListScanner = adjacentListScanner->next;
        }

        // add if not exist in adjacent list
        if (!vertexAdjacentExist)
        {

            singleVertex->adjacencyLast->next = singleadjacent;
            singleVertex->adjacencyLast = singleadjacent;
        }
    }
}

int findShortestDistance(char *source, char *destination)
{

    int shortestDistance = 0;

    if (strcmp(source, destination) == 0)
        return 0;

    // keep adding nodes to heap except source
    Vertex *vertexScanner = firstVertex;
    Vertex *sourceVertex = NULL;
    while (vertexScanner != NULL)
    {

        if (strcmp(vertexScanner->city_name, source) == 0)
        {
            sourceVertex = vertexScanner;
        }
        else
        {
            cityNode *singlecity = (cityNode *)malloc(sizeof(cityNode));
            singlecity->aggregated_weight_offered = INF;
            strcpy(singlecity->city_name, vertexScanner->city_name);
            insert_to_heap(singlecity);
        }
        vertexScanner = vertexScanner->next;
    }

    /*
    printf("\n***********\n");
    displayMinHeap();
    printf("\n***********\n");
    */

    // find adjacent of source & update values in heap
    if (sourceVertex->adjacencyFirst == NULL)
        return 0;

    adjacentNode *adjacentNodeofVertex = sourceVertex->adjacencyFirst;
    while (adjacentNodeofVertex != NULL)
    {

        updateMinheap(adjacentNodeofVertex->city_name, adjacentNodeofVertex->weight);

        adjacentNodeofVertex = adjacentNodeofVertex->next;
    }

        /*
        printf("\n***************\n");
        displayMinHeap();
        printf("\n***************\n");
        */

    // pop from heap and add weight to shortest distance
    while (minheapIndex >= 0)
    {

        cityNode *popMinHeap = delete_from_heap();

        /*
        printf("\n---------------\n");
        displayMinHeap();
        printf("\n---------------\n");
        */

        shortestDistance = popMinHeap->aggregated_weight_offered;
        //printf("\nShortest Distance is : %d\n",shortestDistance);
        //printf("%s %s\n",popMinHeap->city_name,destination);
        if (strcmp(popMinHeap->city_name, destination) == 0)
            return shortestDistance;

        // find popped node in vertex list
        Vertex *poppedVertex = NULL;
        vertexScanner = firstVertex;
        while (vertexScanner != NULL)
        {
            if (strcmp(vertexScanner->city_name, popMinHeap->city_name) == 0)
            {
                poppedVertex = vertexScanner;
                break;
            }
            vertexScanner = vertexScanner->next;
        }

        // update value in heap of adjacent of popped node
        adjacentNodeofVertex = poppedVertex->adjacencyFirst;
        while (adjacentNodeofVertex != NULL)
        {

            updateMinheap(adjacentNodeofVertex->city_name, shortestDistance + adjacentNodeofVertex->weight);

            adjacentNodeofVertex = adjacentNodeofVertex->next;
        }
    }

    // freeheap
    freeHeap();
    return -1;
}

void freeGraph(){
    Vertex *vertexScanner = firstVertex;
    while(vertexScanner!=NULL){
        adjacentNode *adjacentNodeScanner = vertexScanner->adjacencyFirst;
        while(adjacentNodeScanner!=NULL){
            adjacentNode *toDeleteNode = adjacentNodeScanner;
            adjacentNodeScanner = adjacentNodeScanner->next;
            free(toDeleteNode);
        }
        Vertex *vertexToDelete = vertexScanner;
        vertexScanner = vertexScanner->next;
        free(vertexToDelete);
    }
    firstVertex = NULL;
    lastVertex = NULL;
}

//heap
void heapify_bottom(int index){

    cityNode *tempCity;
    int parent;

    while(index != 0){

        parent = (index-1)/2;

        if(minheap[index]->aggregated_weight_offered < minheap[parent]->aggregated_weight_offered ){

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
        else if( (leftChild <= minheapIndex) && (rightChild <= minheapIndex) && (minheap[leftChild]->aggregated_weight_offered <= minheap[rightChild]->aggregated_weight_offered)  && (minheap[index]->aggregated_weight_offered > minheap[leftChild]->aggregated_weight_offered) ){

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

    for(int i=0;i<=minheapIndex;++i){
        if(strcmp(minheap[i]->city_name,cityName) == 0){

            if(minheap[i]->aggregated_weight_offered > weight){

            minheap[i]->aggregated_weight_offered = weight;
            heapify_bottom(i); 

            }
            
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

//End