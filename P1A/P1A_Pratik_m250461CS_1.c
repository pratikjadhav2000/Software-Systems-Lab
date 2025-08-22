#include<stdio.h>
#include<stdbool.h>
#define total_buses 10

bool isFourdigit(int);

int main(){
  
  /*int total_buses = 0;
  printf("Enter the number of buses");
  scanf("%d",total_buses);*/
  
  int buses[total_buses];
  int registration_number = 0;

for(int i=0;i<total_buses;++i){
  char userchoice;
  printf("Press Y to add registration number.Press any key to exit \n");
  userchoice = getchar();
  
        if( userchoice == 'Y' || userchoice == 'y' ){
            
            printf("Enter the registration number of bus %d \n",i);
            scanf("%d",&registration_number);

            while(!isFourdigit(registration_number))
              scanf("%d",&registration_number);
            
            getchar();
        }
        else{
          printf("Exiting... \n");
        break;
        }
        
}

return 0;
}

bool isFourdigit(int registration_number){
  int number_length;
  for(number_length=0;number_length<=5;++number_length){
    if(registration_number == 0)
    break;
    registration_number = registration_number/10;
  }
  
  printf("Number length %d \n",number_length);
  if(registration_number == 0 && number_length == 4)
    return true;
  else{
  printf("Please Enter a valid 4 digit registration number \n");
  return false;
  }
  
}
