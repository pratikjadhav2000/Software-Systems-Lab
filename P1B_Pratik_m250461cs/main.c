#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "bookings.h"
#include "operations.h"

struct Bus *Buses_First = NULL;
struct Bus *Buses_Last = NULL;


int main()
{

  // when you add bus put in correct place to avoid sorting

  int numberOfBuses, arrayPlace;
  char inputChar;
  //scanf("%d", &numberOfBuses);
  char totalbuses[20];
  arrayPlace = 0;
  while((inputChar = getchar()) != '\n'){
    totalbuses[arrayPlace++] = inputChar;
  }
  totalbuses[arrayPlace] = '\0';
  numberOfBuses = atoi(totalbuses);

  // get Buses
  for (int i = 0; i < numberOfBuses; ++i)
  {

    struct Bus *singleBus = (struct Bus *)malloc(sizeof(struct Bus));
    singleBus->List_of_Passengers = NULL;
    singleBus->waiting_list = NULL;
    singleBus->List_of_Passengers_last = NULL;
    singleBus->waiting_list_last = NULL;
    singleBus->next = NULL;
    singleBus->Total_Passengers = 0;
    singleBus->Total_Waiting_Passengers = 0;

    // get bus id
    arrayPlace = 0;
    while ((inputChar = getchar()) != ',')
    {
      singleBus->Bus_Id[arrayPlace++] = inputChar;
    }
    singleBus->Bus_Id[arrayPlace] = '\0';
    // printf("%s ",singleBus->Bus_Id);

    // get bus Capacity
    arrayPlace = 0;
    char stringInteger[20];
    while ((inputChar = getchar()) != ',')
    {
      stringInteger[arrayPlace++] = inputChar;
    }
    stringInteger[arrayPlace] = '\0';
    singleBus->Capacity = atoi(stringInteger);
    // printf("%d ",singleBus->Capacity);
    // Bus capacity handling
    if (singleBus->Capacity < 1 || singleBus->Capacity > 10)
    {
      printf("ERROR: Invalid Capacity");
      exit(1);
    }

    // get bus Driver_name
    arrayPlace = 0;
    while ((inputChar = getchar()) != ',')
    {
      singleBus->Driver_name[arrayPlace++] = inputChar;
    }
    singleBus->Driver_name[arrayPlace] = '\0';
    // printf("%s ",singleBus->Driver_name);

    // get bus Boarding_point
    arrayPlace = 0;
    while ((inputChar = getchar()) != ',')
    {
      singleBus->Boarding_point[arrayPlace++] = inputChar;
    }
    singleBus->Boarding_point[arrayPlace] = '\0';
    // printf("%s ",singleBus->Boarding_point);

    // get bus id
    arrayPlace = 0;
    while ((inputChar = getchar()) != ',' && inputChar != '\n')
    {
      singleBus->Dropping_Point[arrayPlace++] = inputChar;
    }
    singleBus->Dropping_Point[arrayPlace] = '\0';
    // printf("%s\n",singleBus->Dropping_Point);

    // add Buses to linked list
    addBus(singleBus);

  }

  displayBuses(Buses_First);

  // operations
  char operation;
  while ((operation = getchar()) != 'e')
  {

    if (operation == 'a')
    {
      getchar();

      struct Bus *singleBus = (struct Bus *)malloc(sizeof(struct Bus));
      singleBus->List_of_Passengers = NULL;
      singleBus->waiting_list = NULL;
      singleBus->List_of_Passengers_last = NULL;
      singleBus->waiting_list_last = NULL;
      singleBus->next = NULL;
      singleBus->Total_Passengers = 0;
      singleBus->Total_Waiting_Passengers = 0;

      // get bus id
      arrayPlace = 0;
      while ((inputChar = getchar()) != ',')
      {
        singleBus->Bus_Id[arrayPlace++] = inputChar;
      }
      singleBus->Bus_Id[arrayPlace] = '\0';
      // printf("%s ",singleBus->Bus_Id);

      // get bus Capacity
      arrayPlace = 0;
      char stringInteger[20];
      while ((inputChar = getchar()) != ',')
      {
        stringInteger[arrayPlace++] = inputChar;
      }
      stringInteger[arrayPlace] = '\0';
      singleBus->Capacity = atoi(stringInteger);
      // printf("%d ",singleBus->Capacity);
      // Bus capacity handling
      if (singleBus->Capacity < 1 || singleBus->Capacity > 10)
      {
        printf("ERROR: Invalid Capacity");
        exit(1);
      }

      // get bus Driver_name
      arrayPlace = 0;
      while ((inputChar = getchar()) != ',')
      {
        singleBus->Driver_name[arrayPlace++] = inputChar;
      }
      singleBus->Driver_name[arrayPlace] = '\0';
      // printf("%s ",singleBus->Driver_name);

      // get bus Boarding_point
      arrayPlace = 0;
      while ((inputChar = getchar()) != ',')
      {
        singleBus->Boarding_point[arrayPlace++] = inputChar;
      }
      singleBus->Boarding_point[arrayPlace] = '\0';
      // printf("%s ",singleBus->Boarding_point);

      // get bus id
      arrayPlace = 0;
      while ((inputChar = getchar()) != ',' && inputChar != '\n')
      {
        singleBus->Dropping_Point[arrayPlace++] = inputChar;
      }
      singleBus->Dropping_Point[arrayPlace] = '\0';
      // printf("%s\n",singleBus->Dropping_Point);

      addBus(singleBus);
      printf("%s Added\n", singleBus->Bus_Id);
    }

    if (operation == 'b')
    {
      getchar();

      // book a ticket
      struct Passenger *singlePassenger = (struct Passenger *)malloc(sizeof(struct Passenger));
      singlePassenger->previous = NULL;
      singlePassenger->next = NULL;

      // get passenger name
      arrayPlace = 0;
      while ((inputChar = getchar()) != ',')
      {
        singlePassenger->Name[arrayPlace++] = inputChar;
      }
      singlePassenger->Name[arrayPlace] = '\0';
      // printf("%s ",singlePassenger->Name);

      // get passenger mobile
      arrayPlace = 0;
      while ((inputChar = getchar()) != ',')
      {
        singlePassenger->Mobile_No[arrayPlace++] = inputChar;
      }
      singlePassenger->Mobile_No[arrayPlace] = '\0';

      // get passenger boarding point
      arrayPlace = 0;
      while ((inputChar = getchar()) != ',')
      {
        singlePassenger->Boarding_point[arrayPlace++] = inputChar;
      }
      singlePassenger->Boarding_point[arrayPlace] = '\0';
      // printf("%s ",singlePassenger->Boarding_point);

      // get passenger dropping point
      arrayPlace = 0;
      while ((inputChar = getchar()) != ',' && inputChar != '\n')
      {
        singlePassenger->Dropping_Point[arrayPlace++] = inputChar;
      }
      singlePassenger->Dropping_Point[arrayPlace] = '\0';
      // printf("%s ",singlePassenger->Dropping_Point);

      bookTicket(singlePassenger);
    }
    if (operation == 'c')
    {
      getchar();
      char BusID[50];
      int mobileNumber;

      // get BusID
      arrayPlace = 0;
      while ((inputChar = getchar()) != ',')
      {
        BusID[arrayPlace++] = inputChar;
      }
      BusID[arrayPlace] = '\0';
      // printf("%s ",BusID);

      // get passenger mobile number
      arrayPlace = 0;
      char stringMobileNumber[20];
      while ((inputChar = getchar()) != ',' && inputChar != '\n')
      {
        stringMobileNumber[arrayPlace++] = inputChar;
      }
      stringMobileNumber[arrayPlace] = '\0';
      

      cancelBooking(BusID, stringMobileNumber);
    }
    if (operation == 'l')
    {
      getchar();

      char BusID[50];
      int mobileNumber;

      // get BusID
      arrayPlace = 0;
      while ((inputChar = getchar()) != ',' && inputChar != '\n')
      {
        BusID[arrayPlace++] = inputChar;
      }
      BusID[arrayPlace] = '\0';
      // printf("%s ",BusID);

      listPassengers(BusID);
    }
    if (operation == 'k')
    {
      getchar();

      char BusID[50];
      int mobileNumber;

      // get BusID
      arrayPlace = 0;
      while ((inputChar = getchar()) != ',' && inputChar != '\n')
      {
        BusID[arrayPlace++] = inputChar;
      }
      BusID[arrayPlace] = '\0';
      // printf("%s ",BusID);

      countBookings(BusID);
    }
    if (operation == 's')
    {

      displayBuses(Buses_First);
    }
  }

  return 0;
}


