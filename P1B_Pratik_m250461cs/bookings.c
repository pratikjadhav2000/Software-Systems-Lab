#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "bookings.h"
#include "operations.h"
extern struct Bus *Buses_First;
extern struct Bus *Buses_Last;
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

