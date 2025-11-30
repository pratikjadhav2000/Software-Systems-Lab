#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define INF 99999

// structure definitions

// BST
typedef struct Passenger
{

    char name[21], mobile_number[11];
    int travel_count, aggregated_ticket_expense, aggregated_discount_received;
    struct Passenger *left_child, *right_child, *parent;

} Passenger;

// graph
typedef struct adjacentNode
{

    char city_name[30];
    int weight;
    struct adjacentNode *next;

} adjacentNode;

typedef struct vertex
{

    char city_name[30];
    adjacentNode *adjacencyFirst, *adjacencyLast;
    struct vertex *next;

} Vertex;

// heap
typedef struct cityNode
{

    char city_name[30];
    int aggregated_weight_offered;

} cityNode;

// function declarations

// BST
void retainPassengerDetails(Passenger *singlePassenger);
void getInorderTraversal(Passenger *root_BST);
int checkEligible(char *passengerName, char *mobileNumber);
void getMostTraveled();
void freeBST(Passenger *root_BST);

// graph
void addVertex(char *source, char *destination,int edgeWeight);
int findShortestDistance(char *source, char *destination);
void freeGraph();

// heap
void insert_to_heap(cityNode *city);
cityNode *delete_from_heap();
void heapify_bottom(int index);
void heapify_top(int index);
void displayMinHeap();
void freeHeap();
void updateMinheap(char *cityName, int weight);

// global variables

// BST
Passenger *root_BST = NULL;
Passenger *mostTraveled = NULL;
char *passengerNames[100];
int passengerCount = -1;

// graph
Vertex *firstVertex = NULL;
Vertex *lastVertex = NULL;

// heap
cityNode *minheap[100];
int minheapIndex = -1;

int main()
{

    int numberOfPassengers, arrayPlace;
    char inputChar;
    char totalPassengers[20];

    // BST code
    arrayPlace = 0;
    while ((inputChar = getchar()) != '\n')
    {
        totalPassengers[arrayPlace++] = inputChar;
    }
    totalPassengers[arrayPlace] = '\0';
    numberOfPassengers = atoi(totalPassengers);

    for (int i = 0; i < numberOfPassengers; ++i)
    {

        // create node
        Passenger *singlePassenger = (Passenger *)malloc(sizeof(Passenger));
        singlePassenger->left_child = NULL;
        singlePassenger->right_child = NULL;
        singlePassenger->parent = NULL;
        singlePassenger->travel_count = 0;
        singlePassenger->aggregated_ticket_expense = 0;
        singlePassenger->aggregated_discount_received = 0;

        // get passenger name
        arrayPlace = 0;
        while ((inputChar = getchar()) != ',')
        {
            singlePassenger->name[arrayPlace++] = inputChar;
        }
        singlePassenger->name[arrayPlace] = '\0';
        // printf("%s ",singlePassenger->name);

        // name validation
        if (arrayPlace > 21)
        {
            printf("Name length is more than 20.");
            exit(1);
        }

        // get passenger mobile
        arrayPlace = 0;
        while ((inputChar = getchar()) != ',')
        {
            singlePassenger->mobile_number[arrayPlace++] = inputChar;
        }
        singlePassenger->mobile_number[arrayPlace] = '\0';
        // printf("%s ",singlePassenger->mobile_number);

        // mobile validation
        if (arrayPlace > 11)
        {
            printf("Mobile length is more than 10.");
            exit(1);
        }

        // get fare
        arrayPlace = 0;
        char fare[20];
        while ((inputChar = getchar()) != ',')
        {
            fare[arrayPlace++] = inputChar;
        }
        fare[arrayPlace] = '\0';
        singlePassenger->aggregated_ticket_expense = atoi(fare);
        // printf("%s ",fare);

        // get discount
        arrayPlace = 0;
        char discount[20];
        while ((inputChar = getchar()) != '\n')
        {
            discount[arrayPlace++] = inputChar;
        }
        discount[arrayPlace] = '\0';
        singlePassenger->aggregated_discount_received = atoi(discount);
        // printf("%s ",discount);

        // Discount validation
        if (singlePassenger->aggregated_discount_received >= singlePassenger->aggregated_ticket_expense)
        {
            printf("-1\n");
        }
        else
        {
            // add to BST
            retainPassengerDetails(singlePassenger);
        }
    }

    // Graph code
    // get count of total cities
    int numberOfCities;
    char totalcities[20];
    arrayPlace = 0;
    while ((inputChar = getchar()) != '\n')
    {
        totalcities[arrayPlace++] = inputChar;
    }
    totalcities[arrayPlace] = '\0';
    numberOfCities = atoi(totalcities);

    for (int i = 0; i < numberOfCities; ++i)
    {

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
        while ((inputChar = getchar()) != ',')
        {
            destination_city_name[arrayPlace++] = inputChar;
        }
        destination_city_name[arrayPlace] = '\0';
        
        //get edge weight
        char weight[20];
        int edgeWeight;
        arrayPlace = 0;
        while ((inputChar = getchar()) != '\n')
        {
            weight[arrayPlace++] = inputChar;
        }
        weight[arrayPlace] = '\0';
        edgeWeight = atoi(weight);

        // adding vertex call add function 2 times -> add(source,destination) & add(destination,source)
        addVertex(source_city_name, destination_city_name,edgeWeight);
        addVertex(destination_city_name, source_city_name,edgeWeight);
    }

    // print vertices
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

    // operations
    char operation;
    while ((operation = getchar()) != 't')
    {

        if (operation == 'a')
        {
            getchar();

            // create node
            Passenger *singlePassenger = (Passenger *)malloc(sizeof(Passenger));
            singlePassenger->left_child = NULL;
            singlePassenger->right_child = NULL;
            singlePassenger->parent = NULL;
            singlePassenger->travel_count = 0;
            singlePassenger->aggregated_ticket_expense = 0;
            singlePassenger->aggregated_discount_received = 0;

            // get passenger name
            arrayPlace = 0;
            while ((inputChar = getchar()) != ',')
            {
                singlePassenger->name[arrayPlace++] = inputChar;
            }
            singlePassenger->name[arrayPlace] = '\0';
            // printf("%s ",singlePassenger->name);

            // name validation
            if (arrayPlace > 21)
            {
                printf("Name length is more than 20.");
                exit(1);
            }

            // get passenger mobile
            arrayPlace = 0;
            while ((inputChar = getchar()) != ',')
            {
                singlePassenger->mobile_number[arrayPlace++] = inputChar;
            }
            singlePassenger->mobile_number[arrayPlace] = '\0';
            // printf("%s ",singlePassenger->mobile_number);

            // mobile validation
            if (arrayPlace > 11)
            {
                printf("Mobile length is more than 10.");
                exit(1);
            }

            // get fare
            arrayPlace = 0;
            char fare[20];
            while ((inputChar = getchar()) != ',')
            {
                fare[arrayPlace++] = inputChar;
            }
            fare[arrayPlace] = '\0';
            singlePassenger->aggregated_ticket_expense = atoi(fare);
            // printf("%s ",fare);

            // get discount
            arrayPlace = 0;
            char discount[20];
            while ((inputChar = getchar()) != '\n')
            {
                discount[arrayPlace++] = inputChar;
            }
            discount[arrayPlace] = '\0';
            singlePassenger->aggregated_discount_received = atoi(discount);
            // printf("%s ",discount);

            // Discount validation
            if (singlePassenger->aggregated_discount_received >= singlePassenger->aggregated_ticket_expense)
            {
                printf("-1\n");
            }
            else
            {
                // add to BST
                retainPassengerDetails(singlePassenger);
            }
        }
        if (operation == 'p')
        {
            getInorderTraversal(root_BST);
            int i;
            for (i = 0; i < passengerCount; ++i)
            {
                printf("%s,", passengerNames[i]);
                
            }
            printf("%s\n", passengerNames[i]);
            passengerCount = -1;
        }
        if (operation == 'e')
        {
            getchar();

            // get passengerName
            char passengerName[21];
            arrayPlace = 0;
            while ((inputChar = getchar()) != ',')
            {
                passengerName[arrayPlace++] = inputChar;
            }
            passengerName[arrayPlace] = '\0';
            // printf("%s ",passengerName);

            // get passengerMobile
            arrayPlace = 0;
            char passengerMobile[11];
            while ((inputChar = getchar()) != '\n')
            {
                passengerMobile[arrayPlace++] = inputChar;
            }
            passengerMobile[arrayPlace] = '\0';

            printf("%d\n", checkEligible(passengerName, passengerMobile));
        }
        if (operation == 'm')
        {
            getMostTraveled();
        }
        if (operation == 'g')
        {
            getchar();

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

            int ShortestDistance = 0;
            ShortestDistance = findShortestDistance(source_city_name, destination_city_name);
            printf("%d\n", ShortestDistance);
        }
    }
    printf("program terminated");

    // free memory
    freeBST(root_BST);
    freeGraph();
    return 0;
}

// function definitions

void retainPassengerDetails(Passenger *singlePassenger)
{

    Passenger *scanner = root_BST;
    bool passengerfound = false;

    if (root_BST == NULL)
    {
        singlePassenger->travel_count = 1;
        root_BST = singlePassenger;
        mostTraveled = singlePassenger;
    }
    else
    {

        while (scanner != NULL)
        {

            if (strcmp(singlePassenger->name, scanner->name) == 0)
            {
                // found a passenger
                passengerfound = true;
                // printf("Passenger %s",scanner->name);

                // logic to update node values
                scanner->travel_count++;
                scanner->aggregated_ticket_expense = scanner->aggregated_ticket_expense + singlePassenger->aggregated_ticket_expense;
                scanner->aggregated_discount_received = scanner->aggregated_discount_received + singlePassenger->aggregated_discount_received;
                free(singlePassenger);
                singlePassenger = scanner;
                break;
            }
            else if (strcmp(singlePassenger->name, scanner->name) < 0)
            {
                // less than node
                if (scanner->left_child == NULL)
                {
                    singlePassenger->travel_count = 1;
                    scanner->left_child = singlePassenger;
                    break;
                }
                else
                {
                    scanner = scanner->left_child;
                }
            }
            else if (strcmp(singlePassenger->name, scanner->name) > 0)
            {
                // greater than node
                if (scanner->right_child == NULL)
                {
                    singlePassenger->travel_count = 1;
                    scanner->right_child = singlePassenger;
                    break;
                }
                else
                {
                    scanner = scanner->right_child;
                }
            }
        }
    }

    // logic to update most travelled
    if (singlePassenger->travel_count == mostTraveled->travel_count && singlePassenger->aggregated_discount_received > mostTraveled->aggregated_discount_received)
    {

        mostTraveled = singlePassenger;
    }
    else if (singlePassenger->travel_count > mostTraveled->travel_count)
    {
        mostTraveled = singlePassenger;
    }
}

void getInorderTraversal(Passenger *root_BST)
{

    if (root_BST == NULL)
        return;

    getInorderTraversal(root_BST->left_child);
    // printf("%s %s %d %d\n",root_BST->name,root_BST->mobile_number, root_BST->aggregated_ticket_expense,root_BST->aggregated_discount_received);
    passengerNames[++passengerCount] = root_BST->name;
    //printf("%s %d %d,", root_BST->name,root_BST->travel_count,root_BST->aggregated_discount_received); // make global array of strings -> store these and then print it.
    getInorderTraversal(root_BST->right_child);
}

int checkEligible(char *passengerName, char *mobileNumber)
{

    Passenger *scanner = root_BST;
    bool passengerfound = false;

    if (root_BST == NULL)
        return -1;
    else
    {

        while (scanner != NULL)
        {

            if (strcmp(passengerName, scanner->name) == 0 && strcmp(mobileNumber, scanner->mobile_number) == 0)
            {
                // found a passenger
                passengerfound = true;
                // printf("Passenger Found");
                if (scanner->travel_count > 0 && scanner->aggregated_discount_received < 700)
                {
                    return 1;
                }
                else
                {
                    return -1;
                }

                break;
            }
            else if (strcmp(passengerName, scanner->name) < 0)
            {
                // less than node
                scanner = scanner->left_child;
            }
            else if (strcmp(passengerName, scanner->name) > 0)
            {
                // greater than node
                scanner = scanner->right_child;
            }
        }

        if (!passengerfound)
            return 0;
    }
}

void getMostTraveled()
{
    printf("%d,%d\n", mostTraveled->travel_count, mostTraveled->aggregated_discount_received);
}

void freeBST(Passenger *root_BST)
{

    if (root_BST == NULL)
        return;

    freeBST(root_BST->left_child);
    Passenger *rightchild = root_BST->right_child;
    // printf("Deleting %s\n", root_BST->name);
    free(root_BST);
    freeBST(rightchild);
}

// graph
void addVertex(char *source, char *destination,int edgeWeight)
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
    singleadjacent->weight = edgeWeight;
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
        //printf("%s %d",adjacentNodeofVertex->city_name, adjacentNodeofVertex->weight);
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
        // printf("\nShortest Distance is : %d\n",shortestDistance);
        // printf("%s %s\n",popMinHeap->city_name,destination);
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

void freeGraph()
{
    Vertex *vertexScanner = firstVertex;
    while (vertexScanner != NULL)
    {
        adjacentNode *adjacentNodeScanner = vertexScanner->adjacencyFirst;
        while (adjacentNodeScanner != NULL)
        {
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

// heap
void heapify_bottom(int index)
{

    cityNode *tempCity;
    int parent;

    while (index != 0)
    {

        parent = (index - 1) / 2;

        if (minheap[index]->aggregated_weight_offered < minheap[parent]->aggregated_weight_offered)
        {

            // swap with parent
            tempCity = minheap[parent];
            minheap[parent] = minheap[index];
            minheap[index] = tempCity;
            tempCity = NULL;
            index = parent;
        }
        else
        {
            break;
        }
    }
}

void heapify_top(int index)
{

    cityNode *tempCity;
    int leftChild, rightChild;

    while (index <= minheapIndex)
    {

        leftChild = 2 * index + 1;
        rightChild = 2 * index + 2;

        // only left child case
        if ((leftChild <= minheapIndex) && (rightChild > minheapIndex) && (minheap[index]->aggregated_weight_offered > minheap[leftChild]->aggregated_weight_offered))
        {
            // swap with left child
            tempCity = minheap[index];
            minheap[index] = minheap[leftChild];
            minheap[leftChild] = tempCity;
            tempCity = NULL;
            index = leftChild;
        }
        else if ((leftChild <= minheapIndex) && (rightChild <= minheapIndex) && (minheap[leftChild]->aggregated_weight_offered <= minheap[rightChild]->aggregated_weight_offered) && (minheap[index]->aggregated_weight_offered > minheap[leftChild]->aggregated_weight_offered))
        {

            // swap with left child
            tempCity = minheap[index];
            minheap[index] = minheap[leftChild];
            minheap[leftChild] = tempCity;
            tempCity = NULL;
            index = leftChild;
        }
        else if ((leftChild <= minheapIndex) && (rightChild <= minheapIndex) && (minheap[rightChild]->aggregated_weight_offered < minheap[leftChild]->aggregated_weight_offered) && (minheap[index]->aggregated_weight_offered > minheap[rightChild]->aggregated_weight_offered))
        {

            // swap with right child
            tempCity = minheap[index];
            minheap[index] = minheap[rightChild];
            minheap[rightChild] = tempCity;
            tempCity = NULL;
            index = rightChild;
        }
        else
        {
            break;
        }
    }
}

void insert_to_heap(cityNode *city)
{

    ++minheapIndex;
    minheap[minheapIndex] = city;
    heapify_bottom(minheapIndex);
}
cityNode *delete_from_heap()
{

    cityNode *city_to_delete = minheap[0];
    minheap[0] = minheap[minheapIndex];
    minheap[minheapIndex] = NULL;
    minheapIndex--;
    heapify_top(0);

    return city_to_delete;
}

void displayMinHeap()
{

    int newline = 2;
    for (int i = 0; i <= minheapIndex; ++i)
    {
        //printf("%d(%s)", minheap[i]->aggregated_weight_offered,minheap[i]->city_name);
        printf("%d)", minheap[i]->aggregated_weight_offered);

        if (newline - 1 == i + 1)
        {
            printf("\n");
            newline *= 2;
        }
    } 
}

void updateMinheap(char *cityName, int weight)
{

    for (int i = 0; i <= minheapIndex; ++i)
    {
        if (strcmp(minheap[i]->city_name, cityName) == 0)
        {

            if (minheap[i]->aggregated_weight_offered > weight)
            {
                minheap[i]->aggregated_weight_offered = weight;
                heapify_bottom(i);
            }

            break;
        }
    }
}

void freeHeap()
{

    for (int i = 0; i < minheapIndex; ++i)
    {
        free(minheap[i]);
        minheap[i] = NULL;
    }

    minheapIndex = -1;
}

// End
