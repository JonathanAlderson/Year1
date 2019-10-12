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



                      //  I WISH THERE WAS SOME SORT OF DATASTRUCTURE WE COULD
                      //  STORE THESE REPEATED VARAIBLES IN
                      float unitPrice0 = 0.2;
                      float unitPrice1 = 0.35;
                      float unitPrice2 = 0.5;
                      float unitPrice3 = 0.75;
                      float unitPrice4 = 2.5;




                      //  I WISH THERE WAS SOME SORT OF DATASTRUCTURE WE COULD
                      //  STORE THESE REPEATED VARAIBLES IN
                      int waterConsumptionRange0 = 0;
                      int waterConsumptionRange1 = 5;
                      int waterConsumptionRange2 = 12;
                      int waterConsumptionRange3 = 25;
                      int waterConsumptionRange4 = 40;






                      // A Bunch of declerations of variables

                      float amountOfWaterProcessed = 0.95; // This is to represent 95%, can be changed easily, no magic numbers here.

                      float wasteWaterCharge = 0.25; // This represenets £0.25 per liter of water used
                      float commercialWasteWaterCharge = 2.0;

                      float fixedQuaterlyFee = 10.0; // This is the fixed quaterly fee
                      float commercialFixedQuaterlyFee = 50.0;

                      float feePerDay = 0.1; // This is the fee charged for ever liter of water that is used by the custoemr
                      float commercialFeePerDay = 1.3;

                      int daysUsed = 91;
                      float waterProcessingCost = 0.0;
                      float feeForDaysUsedCost = 0.0;
                      float mainWaterUsageCost = 0.0;
                      int customerType;
                      float waterCharge;
                      float waterChargeAfterVAT;
                      int metersCubedUsed;
                      float VATRate = 0.2; // This represents 20%
                      float VAT; // this is only used for commercial customers.
                      int i,j = 0; // Just used for counting loops








                      printf("\n\n\n'1' for Domestic, '2' for Commercial\n\n\n\n\nPlease enter the:\n\n\tCustomer Type: ");
                      scanf("%i",&customerType);
                      printf("\n\n\tWater Consumption: ");
                      scanf("%i",&metersCubedUsed);


                    	if(customerType == 2)
                    	{

                        waterCharge = 0;


                        waterProcessingCost = amountOfWaterProcessed*commercialWasteWaterCharge * metersCubedUsed;
                        mainWaterUsageCost = unitPrice4 * metersCubedUsed;
                        feeForDaysUsedCost = daysUsed * commercialFeePerDay;
                        waterCharge = mainWaterUsageCost + waterProcessingCost + feeForDaysUsedCost + commercialFixedQuaterlyFee;
                        VAT = waterCharge * VATRate;

                        waterChargeAfterVAT = waterCharge + VAT;

                        printf("\n\n\nProcessing Commercial Bill:\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
                        printf("  \t╔═══════════════════════╦═════════════════════════════════╗");
                        printf("\n\t║Fresh Water:           ║  £%-30.2f║",mainWaterUsageCost);
                        printf("\n\t╠═══════════════════════╬═════════════════════════════════╣");
                        printf("\n\t║Waste Water:           ║  £%-30.2f║",waterProcessingCost);
                        printf("\n\t╠═══════════════════════╬═════════════════════════════════╣");
                        printf("\n\t║Fixed Fee:             ║  £%-30.2f║",commercialFixedQuaterlyFee);
                        printf("\n\t╠═══════════════════════╬═════════════════════════════════╣");
                        printf("\n\t║Daily Standing Charge: ║  £%-30.2f║",feeForDaysUsedCost);
                        printf("\n\t╠═══════════════════════╬═════════════════════════════════╣");
                        printf("\n\t║Pre Tax Total:         ║  £%-30.2f║",waterCharge);
                        printf("\n\t╠═══════════════════════╬═════════════════════════════════╣");
                        printf("\n\t║Value Added Tax:       ║  £%-30.2f║",VAT);
                        printf("\n\t╚═══════════════════════╩═════════════════════════════════╝");
                      	printf("\n\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\nTotal: £%.2f\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n",waterChargeAfterVAT);
                        printf("\n\n\n\n\tPress enter to continue...");
                        getchar();
                        getchar();

                    	}

                    	if(customerType == 1)
                    	{
                        waterCharge = 0;
                        mainWaterUsageCost = 0;
                    		//Waste water processing
                    		waterProcessingCost = amountOfWaterProcessed*metersCubedUsed*wasteWaterCharge;
                    		waterCharge = waterCharge + waterProcessingCost ;



                    		//Fixed fee, this can be changed from the main menu
                    		waterCharge = waterCharge + fixedQuaterlyFee;



                    		//Fee per liter
                    		feeForDaysUsedCost = feePerDay*daysUsed;
                    		waterCharge = waterCharge + feeForDaysUsedCost;


                        metersCubedUsed++; // This is done, since one is taken away
                                           // at the start of every while loop,
                                          //rather than at the end of every while loop.

                    		// Main water billing
                        while(metersCubedUsed > 0)
                        {
                          metersCubedUsed = metersCubedUsed-1;
                          if(metersCubedUsed > waterConsumptionRange4)
                          {
                            mainWaterUsageCost = mainWaterUsageCost + unitPrice4;
                            continue;
                          }

                          if(metersCubedUsed > waterConsumptionRange3)
                          {
                            mainWaterUsageCost = mainWaterUsageCost + unitPrice3;
                            continue;
                          }

                          if(metersCubedUsed > waterConsumptionRange2)
                          {
                            mainWaterUsageCost = mainWaterUsageCost + unitPrice2;
                            continue;
                          }

                          if(metersCubedUsed > waterConsumptionRange1)
                          {
                            mainWaterUsageCost = mainWaterUsageCost + unitPrice1;
                            continue;
                          }

                          if(metersCubedUsed > waterConsumptionRange0)
                          {
                            mainWaterUsageCost = mainWaterUsageCost + unitPrice0;
                            continue;
                          }

                        }

                        waterCharge = waterCharge + mainWaterUsageCost;

                        printf("\n\n\nProcessing Domestic Bill:\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
                        printf("  \t╔═══════════════════════╦═════════════════════════════════╗");
                        printf("\n\t║Fresh Water:           ║  £%-30.2f║",mainWaterUsageCost);
                        printf("\n\t╠═══════════════════════╬═════════════════════════════════╣");
                        printf("\n\t║Waste Water:           ║  £%-30.2f║",waterProcessingCost);
                        printf("\n\t╠═══════════════════════╬═════════════════════════════════╣");
                        printf("\n\t║Fixed Fee:             ║  £%-30.2f║",fixedQuaterlyFee);
                        printf("\n\t╠═══════════════════════╬═════════════════════════════════╣");
                        printf("\n\t║Daily Standing Charge: ║  £%-30.2f║",feeForDaysUsedCost);
                        printf("\n\t╚═══════════════════════╩═════════════════════════════════╝");
                        printf("\n\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\nTotal: £%.2f\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n",waterCharge);
                        printf("\n\n\n\n\tPress enter to continue...");
                        getchar();
                        getchar();



                    	}



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
        printf("\tNow exiting...\n\n\n\n\n\n\n\n");
        exit(1);

      }
    }

    else
      printf("\n\n\tPlease enter a valid choice, either '1','2' or '3'\n\n");
  }
	return 0;
}


#
/*

I had a much more efiecnt way of calulating
the water cost by using arrays and iterating
through them nicely
It's a shame I can't use them, but I didn't want
to delete it, so I've kept it down here.

while(metersCubedUsed > 0)
{
  i = 0;
  while(waterConsumptionRange[i] < metersCubedUsed)
  {
    i++;
  }
  waterCharge = waterCharge + unitPrice[i];
  mainWaterUsageCost = mainWaterUsageCost + unitPrice[i];
  metersCubedUsed --;
}

printf("\n\n\nSums and Statistics:\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
printf("  \t╔═══════════════════════╦═════════════════════════════════╗");
printf("\n\t║ Total Fresh Water Consumption:           ║  £%-30.2f║",mainWaterUsageCost);
printf("\n\t╠═══════════════════════╬═════════════════════════════════╣");
printf("\n\t║ Total Fresh Water For Domestic Consumers:           ║  £%-30.2f║",waterProcessingCost);
printf("\n\t╠═══════════════════════╬═════════════════════════════════╣");
printf("\n\t║ Total Revenue:             ║  £%-30.2f║",fixedQuaterlyFee);
printf("\n\t╠═══════════════════════╬═════════════════════════════════╣");
printf("\n\t║ Cost of Providing Water: ║  £%-30.2f║",feeForDaysUsedCost);
printf("\n\t╠═══════════════════════╬═════════════════════════════════╣");
printf("\n\t║ Profit:           ║  £%-30.2f║",waterProcessingCost);
printf("\n\t╠═══════════════════════╬═════════════════════════════════╣");
printf("\n\t║ Income Tax To Pay:             ║  £%-30.2f║",fixedQuaterlyFee);
printf("\n\t╠═══════════════════════╬═════════════════════════════════╣");
printf("\n\t║ Average Domestic Consumer Bill: ║  £%-30.2f║",feeForDaysUsedCost);
printf("\n\t╠═══════════════════════╬═════════════════════════════════╣");
printf("\n\t║ Maximum Domestic Bill: ║  £%-30.2f║",feeForDaysUsedCost);
printf("\n\t╚═══════════════════════╩═════════════════════════════════╝");
printf("\n\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\nTotal: £%.2f\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n",waterCharge);
printf("\n\n\n\n\tPress enter to continue...");
getchar();
getchar();



*/
