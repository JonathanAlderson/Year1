import java.io.*;
import java.util.Scanner;


public class Pollution
{
    public static void main(String []args)
    {

      String fileName = "";
      // Checking if user has supplied a file name
      try
      {
        fileName = args[0];
      }
      catch(ArrayIndexOutOfBoundsException e)
      {
        System.out.printf("\n\nPlease run with a csv file in parameters,\nusage 'Java Pollution example.csv'.\n\n");
        // helpful message to the user so that they know what to input
        return;
      }

      PollutionDataset firstDataset = new PollutionDataset();

      // Tests if file exists and is valid to read
      try
      {
        firstDataset.readCSV(fileName);
      }
      catch(FileNotFoundException e)
      {
        System.out.printf("\n\nFile not found\nPlease enter a file, ending with .csv\n\n");
        return;
      }
      catch(DataException e)
      {
        System.out.printf("\n\nFile processing error,\nfile may be corrupt\n"); // helpful error message for the user.
        return;
      }

      // Printing out information
      System.out.printf("\n\nProcessing " + fileName + " please wait.\n\n"); // useful for the user, so that they know the program has not crashed
      System.out.printf("\n" + firstDataset.size() + " records processed\nMax: " + firstDataset.maxLevel() + "\nMin: " + firstDataset.minLevel() + "\nAvg: " + firstDataset.meanLevel() + " \u00b5.g/m\u00b3.\nBreaches: \n\n");

      if(firstDataset.dayRulesBreached() != null)
      {
        System.out.printf("EU Rules Breached on " + firstDataset.dayRulesBreached() + "\n\n\n");
      }
      else
      {
        System.out.println("EU Rules Not Breached.\n\n\n");
      }
    }

}
