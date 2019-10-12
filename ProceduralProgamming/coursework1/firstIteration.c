/********************************************************************

I declare that the following program was written by me and that I have NOT copied any part of this code from any other source.

Name: Jonathan Alderson

Email: sc17j3a@leeds.ac.uk

Date: 14/10/17

********************************************************************/



#include <stdio.h>
#include <math.h>
#include <stdlib.h>



int main()
{
  while(1<2)
  {
    int userChoice;
    char continueVar = 0;
    printf("\e[1;1H\e[2J");
    printf("1. Compute and Print the Bill for a Customer\n2. Show Sums and Statistics\n3. Quit the program\n\nPlease enter your choice (1,2, or 3):");
    scanf("%i",&userChoice);

    if(userChoice == 1 || userChoice == 2 || userChoice == 3)
    {
      if(userChoice == 1)
      {
        printf("\n\n\tThis option is not yet implemented.\n\nPress enter to continue...");
        getchar();
        getchar(); // I hate C, to get this to work, you must write getchar() twice or else it won't work, how odd.

      }

      if(userChoice == 2)
      {
        printf("\n\n\tThis option is not yet implemented.\n\nPress enter to continue...");
        getchar();
        getchar();
      }

      if(userChoice == 3)
      {
        printf("\e[1;1H\e[2J");
        printf("\tNow exiting...\n\n\n");
        exit(1);

      }
    }

    else
      printf("\n\n\tPlease enter a valid choice, either '1','2' or '3'\n\n");
  }
	return 0;
}
