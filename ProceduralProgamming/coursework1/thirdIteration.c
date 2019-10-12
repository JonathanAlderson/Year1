/********************************************************************

I declare that the following program was written by me and that I have NOT copied any part of this code from any other source.

Name: Jonathan Alderson

Email: sc17j3a@leeds.ac.uk

Date: 14/10/17

********************************************************************/




// FINSHED 10:28 TUESDAY 10TH OCTOBER 2017









// JONATHAN ALDERSON









// sc17j3a





/*

READ-ME

I thought this coursework was very fun,
I quite enjoy the simplicity of the
terminal based programs, not having to worry
about graphics and making it look too pretty.
I tried my best to create some nice looking
graphics for the whole thing, and add some more
features, such as showing, minimums and maximums
for both the domestic and consumer options.

I would have liked to add a persistent store of data,
since it seems a little pointless having to reenter
all of the data every time the program is relaunched.

Some nice graphs would have been nice aswell, But
that would have required some arrays to do nicely.

I tried to challenge myself to complete the
assessment on the first day, and I'm happy
I did, I know it doesn't does not matter,
but hopefully this shows that I like programming
at least.



Jonathan ALDERSON

sc17j3a...


*/


// Water Company Coursework

#include <stdio.h>
#include <math.h>
#include <stdlib.h>



int main()
{

  // These are some variables which are declared to keep track
  // of sums and Statistics
  float totalFreshWaterConsumption = 0;
  float totalDomesticFreshWaterConsumption = 0;
  float totalCommercialFreshWaterComsumption = 0;
  float totalRevenue = 0;
  float providingWaterCost = 0;
  float profit = 0;
  float incomeTax = 0;
  float averageDomesticConsumerBill = 0;
  float averageCommercialBill = 0;
  float maximumDomesticBill = 0;
  float minimumDomesticBill = 0;
  float maximumCommercialBill = 0;
  float minimumCommercialBill = 0;
  float totalDomesticBill = 0;
  float totalCommercialBill = 0;
  int numberOfDomesticCustomers = 0;
  int numberOfCommercialCustomers = 0;
  float costOfOneCubicMeter = 1.0;
  float incomeTaxRate = 0.25;


  // These variables are here to stop the summary table printing errors when no data has been inputted yet...

  int commercialUsed = 0;
  int domesticUsed = 0;




  //  I WISH THERE WAS SOME SORT OF DATASTRUCTURE WE COULD
  //  STORE THESE REPEATED VARAIBLES IN

  // These variables are used for the tariff
  float unitPrice0 = 0.2;
  float unitPrice1 = 0.35;
  float unitPrice2 = 0.5;
  float unitPrice3 = 0.75;
  float unitPrice4 = 2.5;


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



  while(1<2) // This loop will go on forever
  {
    int userChoice;
    char continueVar = 0;
    printf("\e[1;1H\e[2J"); // This clears the whole terminal, to give a clean look
    printf("1. Compute and Print the Bill for a Customer\n2. Show Sums and Statistics\n3. Quit the program\n\nPlease enter your choice (1,2, or 3):");
    scanf("%i",&userChoice);

    if(userChoice == 1 || userChoice == 2 || userChoice == 3) //Checks that all of the inputs are correct and gives an error if not
    {
      if(userChoice == 1)
      {

                      printf("\n\n\n'1' for Domestic, '2' for Commercial\n\n\n\n\nPlease enter the:\n\n\tCustomer Type: ");
                      scanf("%i",&customerType);
                      printf("\n\n\tWater Consumption: ");
                      scanf("%i",&metersCubedUsed);



                      //}

                    	if(customerType == 2)
                    	{

                        waterCharge = 0;


                        waterProcessingCost = amountOfWaterProcessed*commercialWasteWaterCharge * metersCubedUsed;
                        mainWaterUsageCost = unitPrice4 * metersCubedUsed;
                        feeForDaysUsedCost = daysUsed * commercialFeePerDay;
                        waterCharge = mainWaterUsageCost + waterProcessingCost + feeForDaysUsedCost + commercialFixedQuaterlyFee;
                        VAT = waterCharge * VATRate;

                        waterChargeAfterVAT = waterCharge + VAT;


                        //Updating the main variables for sums and Statistics
                        totalFreshWaterConsumption = totalFreshWaterConsumption + metersCubedUsed;
                        totalCommercialFreshWaterComsumption = totalCommercialFreshWaterComsumption + metersCubedUsed;
                        totalRevenue = totalRevenue + waterCharge;


                        numberOfCommercialCustomers = numberOfCommercialCustomers + 1;
                        totalCommercialBill = totalCommercialBill + waterChargeAfterVAT;

                        if(waterChargeAfterVAT > maximumCommercialBill)
                            maximumCommercialBill = waterChargeAfterVAT;

                        if(waterChargeAfterVAT < minimumCommercialBill || commercialUsed == 0)
                            minimumCommercialBill = waterChargeAfterVAT;

                        //These is a 'boolean' so now the summary table knows it can process averages without dividing by 0
                        commercialUsed = 1;

                        // I am very proud of the way these tables look
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



                        // Updating the main total for fresh water used,
                        // it must be done here, since the next while loop
                        // decrements the metersCubedUsed variable
                        totalFreshWaterConsumption = totalFreshWaterConsumption + metersCubedUsed;
                        totalDomesticFreshWaterConsumption = totalDomesticFreshWaterConsumption + metersCubedUsed;





                        metersCubedUsed++; // This is done, since one is taken away
                                           // at the start of every while loop,
                                          //rather than at the end of every while loop.
                                          // Updating the main totalFreshWaterConsumption





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

                        // Updating some of the main varaibles for sums and Statistics

                        totalRevenue = totalRevenue + waterCharge;

                        numberOfDomesticCustomers = numberOfDomesticCustomers + 1;
                        totalDomesticBill = totalDomesticBill + waterCharge;

                        if(waterCharge > maximumDomesticBill)
                            maximumDomesticBill = waterCharge;

                        if(waterCharge < minimumDomesticBill || domesticUsed == 0)
                            minimumDomesticBill = waterCharge;

                        //These is a 'boolean' so now the summary table knows it can process averages without dividing by 0
                        domesticUsed = 1;


                        // Getting the formatting on these tables took a very long time.

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

        // Calculating some numbers to use in the sums and Statistics
        providingWaterCost = totalFreshWaterConsumption * costOfOneCubicMeter;
        profit = totalRevenue - providingWaterCost;
        incomeTax = profit * incomeTaxRate;
        if(commercialUsed == 1)
          averageCommercialBill = totalCommercialBill / (float)numberOfCommercialCustomers;
        else
            averageCommercialBill = 0;



        if(domesticUsed == 1)
          averageDomesticConsumerBill = totalDomesticBill / (float)numberOfDomesticCustomers;
        else
            averageDomesticConsumerBill = 0;




        printf("\n\n\nSums and Statistics:\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
        printf("  \t╔═══════════════════════════════════════════════╦══════════════════╗");
        printf("\n\t║ Total Fresh Water Consumption:                ║   %-15.2f║",totalFreshWaterConsumption);
        printf("\n\t╠═══════════════════════════════════════════════╬══════════════════╣");
        printf("\n\t║ Total Fresh Water For Domestic Consumers:     ║   %-15.2f║",totalDomesticFreshWaterConsumption);
        printf("\n\t╠═══════════════════════════════════════════════╬══════════════════╣");
        printf("\n\t║ Total Fresh Water For Commercial Consumers:   ║   %-15.2f║",totalCommercialFreshWaterComsumption);
        printf("\n\t╠═══════════════════════════════════════════════╬══════════════════╣");
        printf("\n\t║ Total Revenue:                                ║  £%-15.2f║",totalRevenue);
        printf("\n\t╠═══════════════════════════════════════════════╬══════════════════╣");
        printf("\n\t║ Cost of Providing Water:                      ║  £%-15.2f║",providingWaterCost);
        printf("\n\t╠═══════════════════════════════════════════════╬══════════════════╣");
        printf("\n\t║ Profit:                                       ║  £%-15.2f║",profit);
        printf("\n\t╠═══════════════════════════════════════════════╬══════════════════╣");
        printf("\n\t║ Income Tax To Pay:                            ║  £%-15.2f║",incomeTax);
        printf("\n\t╠═══════════════════════════════════════════════╬══════════════════╣");
        printf("\n\t║ Average Domestic Consumer Bill:               ║  £%-15.2f║",averageDomesticConsumerBill);
        printf("\n\t╠═══════════════════════════════════════════════╬══════════════════╣");
        printf("\n\t║ Average Commercial Consumer Bill:             ║  £%-15.2f║",averageCommercialBill);
        printf("\n\t╠═══════════════════════════════════════════════╬══════════════════╣");
        printf("\n\t║ Maximum Domestic Bill:                        ║  £%-15.2f║",maximumDomesticBill);
        printf("\n\t╠═══════════════════════════════════════════════╬══════════════════╣");
        printf("\n\t║ Minumum Domestic Bill:                        ║  £%-15.2f║",minimumDomesticBill);
        printf("\n\t╠═══════════════════════════════════════════════╬══════════════════╣");
        printf("\n\t║ Maximum Commercial Bill:                      ║  £%-15.2f║",maximumCommercialBill);
        printf("\n\t╠═══════════════════════════════════════════════╬══════════════════╣");
        printf("\n\t║ Minumum Commercial Bill:                      ║  £%-15.2f║",minimumCommercialBill);
        printf("\n\t╚═══════════════════════════════════════════════╩══════════════════╝");
        printf("\n\n\n\n\tPress enter to continue...");
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
    {
      printf("\n\n\tPlease enter a valid choice, either '1','2' or '3'\n\n");
      printf("\n\n\n\n\tPress enter to continue...");
      getchar();
      getchar();
    }
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





*/