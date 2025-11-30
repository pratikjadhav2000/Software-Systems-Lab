#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "operations.h"
#include "bookings.h"
extern struct Bus *Buses_First;
extern struct Bus *Buses_Last;
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