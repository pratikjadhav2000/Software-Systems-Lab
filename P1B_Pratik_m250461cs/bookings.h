#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "operations.h"
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
void displayBuses(struct Bus *singleBus);
