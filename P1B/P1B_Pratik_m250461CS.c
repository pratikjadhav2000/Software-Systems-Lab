#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct Bus *Buses_First = NULL;
struct Bus *Buses_Last = NULL;

// structure definitions
struct Passenger
{

  char Name[50], Boarding_point[50], Dropping_Point[50];
  char Mobile_No[20];
  struct Passenger *previous, *next;
};

struct Bus
{

  char Bus_Id[50], Driver_name[50], Boarding_point[50], Dropping_Point[50];
  int Capacity, Total_Passengers, Total_Waiting_Passengers;
  bool isFull;
  struct Passenger *List_of_Passengers, *List_of_Passengers_last, *waiting_list, *waiting_list_last;
  struct Bus *next;
  struct Bus *last;
};

struct Bookings
{

  char Name[50], Boarding_point[50], Dropping_Point[50];
  int Mobile_No;
  char Bus_Id[50];
};

// function declarations
void addBus(struct Bus *singleBus);
void bookTicket(struct Passenger *singlePerson);
void cancelBooking(char *Bus_Id, char* Mobile_No);
void listPassengers(char *Bus_Id);
void countBookings(char *Bus_Id);
void displayBuses(struct Bus *singleBus);

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
    singleBus->last = NULL;
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
    if (Buses_First == NULL)
    {
      Buses_First = singleBus;
      Buses_Last = singleBus;
    }
    else
    {
      Buses_Last->next = singleBus;
      Buses_Last = singleBus;
    }
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
      singleBus->last = NULL;
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

void displayBuses(struct Bus *singleBus)
{

  if (singleBus == NULL)
  {
    printf("Empty List\n");
  }

  while (singleBus != NULL)
  {

    printf("%s,%d,%s,%s,%s\n", singleBus->Bus_Id, singleBus->Capacity, singleBus->Driver_name, singleBus->Boarding_point, singleBus->Dropping_Point);
    singleBus = singleBus->next;
  }
}

void addBus(struct Bus *singleBus)
{

  if (Buses_First == NULL)
  {
    Buses_First = singleBus;
    Buses_Last = singleBus;
  }
  else
  {
    Buses_Last->next = singleBus;
    Buses_Last = singleBus;
  }
  printf("%s Added\n", singleBus->Bus_Id);
}

void bookTicket(struct Passenger *singlePerson)
{

  struct Bus *BusFinder = Buses_First;
  bool busfound = false;

  while (BusFinder != NULL)
  {

    if (!strcmp(singlePerson->Boarding_point, BusFinder->Boarding_point) && !strcmp(singlePerson->Dropping_Point, BusFinder->Dropping_Point))
    {
      busfound = true;
      if (BusFinder->Total_Passengers < BusFinder->Capacity)
      {
        // book ticket if bus found
        if (BusFinder->List_of_Passengers == NULL)
        {
          BusFinder->List_of_Passengers = singlePerson;
          BusFinder->List_of_Passengers_last = singlePerson;
        }
        else
        {
          BusFinder->List_of_Passengers_last->next = singlePerson;
          singlePerson->previous = BusFinder->List_of_Passengers_last;
          BusFinder->List_of_Passengers_last = singlePerson;
        }

        BusFinder->Total_Passengers++;
        printf("%s\n", BusFinder->Bus_Id);
      }
      else
      {
        // if Bus full add to waiting list
        BusFinder->isFull = true;
        if (BusFinder->waiting_list == NULL)
        {
          BusFinder->waiting_list = singlePerson;
          BusFinder->waiting_list_last = singlePerson;
        }
        else
        {
          BusFinder->waiting_list_last->next = singlePerson;
          singlePerson->previous = BusFinder->waiting_list_last;
          BusFinder->waiting_list_last = singlePerson;
        }

        BusFinder->Total_Waiting_Passengers++;
        printf("Waiting %s\n", BusFinder->Bus_Id);
      }

      break;
    }

    BusFinder = BusFinder->next;
  }
  if (busfound == false)
  {
    printf("BUS NOT FOUND\n");
  }
}

void cancelBooking(char *Bus_Id, char* Mobile_No)
{
  struct Bus *BusFinder = Buses_First;
  bool busfound = false;

  while (BusFinder != NULL)
  {

    if ( !strcmp(Bus_Id, BusFinder->Bus_Id) )
    {
      //printf("\n found bus \n");
      // bus found
      busfound = true;

      bool passngerfound = false;
      struct Passenger *Passengger_Finder = BusFinder->List_of_Passengers;
      while (Passengger_Finder != NULL)
      {
        //printf("\n name : %s \n",Passengger_Finder->Name);
        if (!strcmp(Mobile_No,Passengger_Finder->Mobile_No))
        {
          passngerfound = true;
          // passenger found
          //printf("\n number : %s currentnumber : %s\n",Mobile_No,Passengger_Finder->Mobile_No);
          if (Passengger_Finder->previous == NULL)
          {
            BusFinder->List_of_Passengers = Passengger_Finder->next;
            Passengger_Finder->next->previous = NULL;
          }
          else
          {
            Passengger_Finder->previous->next = Passengger_Finder->next;
            Passengger_Finder->next->previous = Passengger_Finder->previous;
          }
          
          //free(Passengger_Finder);
          BusFinder->Total_Passengers--;

          if (BusFinder->isFull)
          {
            
            BusFinder->isFull = false;
            // if bus is full add passenger from waiting list
            if (BusFinder->waiting_list != NULL)
            {
              
              // add in passenger list
              struct Passenger *waiter = BusFinder->waiting_list;
              BusFinder->waiting_list = waiter->next;
              if(waiter->next!=NULL){
                waiter->next->previous = NULL;
                waiter->next = NULL;
              }
              
              

              BusFinder->List_of_Passengers_last->next = waiter;
              waiter->previous = BusFinder->List_of_Passengers_last;
              BusFinder->List_of_Passengers_last = waiter;

              

              BusFinder->Total_Passengers++;
              BusFinder->Total_Waiting_Passengers--;
              printf("%s Added\n", waiter->Name);
            }
          }
        }

        Passengger_Finder = Passengger_Finder->next;
      }

      if (passngerfound == false)
      {
        printf("BOOKING NOT FOUND\n");
      }

      break;
    }

    BusFinder = BusFinder->next;
  }
  if (busfound == false)
  {
    printf("BUS NOT FOUND \n");
  }
}

void listPassengers(char *Bus_Id)
{

  struct Bus *BusFinder = Buses_First;
  while (BusFinder != NULL)
  {

    if (!strcmp(BusFinder->Bus_Id, Bus_Id))
    {
      // bus found
      struct Passenger *Passengers = BusFinder->List_of_Passengers;

      // print the passengers
      while (Passengers != NULL)
      {

        printf("%s,%s,%s,%s\n", Passengers->Name, Passengers->Mobile_No, Passengers->Boarding_point, Passengers->Dropping_Point);

        Passengers = Passengers->next;
      }

      break;
    }

    BusFinder = BusFinder->next;
  }
}

void countBookings(char *Bus_Id)
{

  struct Bus *BusFinder = Buses_First;
  while (BusFinder != NULL)
  {

    if (!strcmp(BusFinder->Bus_Id, Bus_Id))
    {
      // bus found
      printf("%d\n", BusFinder->Total_Waiting_Passengers);
      break;
    }

    BusFinder = BusFinder->next;
  }
}
