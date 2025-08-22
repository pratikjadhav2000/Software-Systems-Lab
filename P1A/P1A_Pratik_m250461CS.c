#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

struct bus
{
    char registration_no[50], driver_name[50], route[50];
    int capacity;
    float fuel_level, mileage;
};

void displayBus(struct bus *busptr);
struct bus *readBus(struct bus *busptr, char *busdetails);
char *getDriver(char *registration_no, struct bus **busptr, int sizeofBuses);
void freeMemory(struct bus **buses, int sizeofBuses);

int main(int argc, char *argv[])
{
    // determine the count of buses
    int BusLength = 0;
    char singleBusdetails[100];
    FILE *fleetlist = fopen(argv[1], "r");
    if (fleetlist == NULL)
    {
        printf("Error opening file.");
    }
    while (fgets(singleBusdetails, 100, fleetlist))
    {
        BusLength++;
    }
    fclose(fleetlist);
    // printf("%d",BusLength);
    struct bus *buses[BusLength];

    // open files & read details and store it in a struct dynamic
    // char *busdetails = "TN09XY5678 Pratik Satara 50 50.8023 70.80";

    fleetlist = fopen(argv[1], "r");
    if (fleetlist == NULL)
    {
        printf("Error opening file.");
    }

    // reading file line by line
    int busNumber = 0;

    while (fgets(singleBusdetails, 100, fleetlist))
    {

        // printf("%s",singleBusdetails);
        struct bus *busptr;
        busptr = (struct bus *)malloc(sizeof(struct bus));

        buses[busNumber++] = readBus(busptr, singleBusdetails);
        // displayBus(busptr);
    }

    fclose(fleetlist);

    // Display bus details
    printf("Bus Details: \n");
    for (size_t i = 0; i < BusLength; i++)
    {
        displayBus(buses[i]);
    }

    // get driver based on registration number
    char registration_number[20];
    printf("\nSearch driver for Registration Number: \n");
    scanf("%s", registration_number);
    char *driverName = getDriver(registration_number, buses, BusLength);
    if (!(strcmp(driverName, "NotAvailable")))
    {
        printf("Not found \n");
    }
    else
    {
        printf("%s", driverName);
    }

    // free memory
    freeMemory(buses, BusLength);

    return 0;
}

void displayBus(struct bus *busptr)
{

    printf("%s ", busptr->registration_no);
    printf("%s ", busptr->driver_name);
    printf("%s ", busptr->route);
    printf("%d ", busptr->capacity);
    printf("%.2f ", busptr->fuel_level);
    printf("%.2f \n", busptr->mileage);
}
struct bus *readBus(struct bus *busptr, char *busdetails)
{
    // handling for different names
    // count tabs
    int tabs = 0;
    char *scanner, endChecker;
    scanner = busdetails;
    while (*scanner != '\n')
    {
        if (*scanner == ' ' && *(scanner + 1) != '\n')
            tabs++;
        scanner++;
    }
    // printf("\n %d \n",tabs); //5 for first name

    char *reader;
    int arrayPlace;

    reader = busdetails;

    // read registration number
    arrayPlace = 0;
    while (*reader != ' ')
    {
        busptr->registration_no[arrayPlace] = *reader;
        arrayPlace++;
        reader++;
    }
    busptr->registration_no[arrayPlace] = 0;
    reader++;
    // printf("%s ",busptr->registration_no);

    // read driver_name number
    arrayPlace = 0;
    while (*reader != ' ')
    {
        busptr->driver_name[arrayPlace] = *reader;
        arrayPlace++;
        reader++;
    }
    busptr->driver_name[arrayPlace] = 0;
    reader++;
    // printf("%s ",busptr->driver_name);

    if (tabs == 6 || tabs == 7 || tabs == 8)
    {
        busptr->driver_name[arrayPlace] = ' ';
        arrayPlace++;
        while (*reader != ' ')
        {
            busptr->driver_name[arrayPlace] = *reader;
            arrayPlace++;
            reader++;
        }
        busptr->driver_name[arrayPlace] = 0;
        reader++;
    }

    if (tabs == 7 || tabs == 8)
    {
        busptr->driver_name[arrayPlace] = ' ';
        arrayPlace++;
        while (*reader != ' ')
        {
            busptr->driver_name[arrayPlace] = *reader;
            arrayPlace++;
            reader++;
        }
        busptr->driver_name[arrayPlace] = 0;
        reader++;
    }

    // read route number
    arrayPlace = 0;
    while (*reader != ' ')
    {
        busptr->route[arrayPlace] = *reader;
        arrayPlace++;
        reader++;
    }
    busptr->route[arrayPlace] = 0;
    reader++;
    // printf("%s ",busptr->route);

    // read capacity number
    arrayPlace = 0;
    char capacity[10];
    while (*reader != ' ')
    {
        capacity[arrayPlace] = *reader;
        arrayPlace++;
        reader++;
    }
    capacity[arrayPlace] = 0;
    busptr->capacity = atoi(capacity);
    reader++;
    // printf("%d ",busptr->capacity);

    // read fuel_level number
    arrayPlace = 0;
    char fuel_level[10];
    while (*reader != ' ')
    {
        fuel_level[arrayPlace] = *reader;
        arrayPlace++;
        reader++;
    }
    fuel_level[arrayPlace] = 0;
    busptr->fuel_level = atof(fuel_level);
    reader++;
    // printf("%f ",busptr->fuel_level);

    // read mileage number
    arrayPlace = 0;
    char mileage[10];
    while ((*reader != ' ') && (*reader != '\n'))
    {
        mileage[arrayPlace] = *reader;
        arrayPlace++;
        reader++;
    }
    mileage[arrayPlace] = 0;
    busptr->mileage = atof(mileage);
    reader++;
    // printf("%f ",busptr->mileage);

    return busptr;
}

char *getDriver(char *registration_no, struct bus **buses, int sizeofBuses)
{

    int result = 1;
    struct bus *busptr;
    for (int i = 0; i < sizeofBuses; ++i)
    {
        busptr = *buses;
        // printf("%s %s \n",registration_no,busptr->registration_no);
        if (!(strcmp(registration_no, busptr->registration_no)))
            return busptr->driver_name;
        ++buses;
    }
    return "NotAvailable";
}

void freeMemory(struct bus **buses, int sizeofBuses)
{

    struct bus *busptr;
    for (int i = 0; i < sizeofBuses; ++i)
    {

        busptr = *buses;
        free(busptr);
        busptr = NULL;

        buses++;
    }
}