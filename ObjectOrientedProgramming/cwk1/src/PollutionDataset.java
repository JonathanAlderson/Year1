import java.io.FileNotFoundException;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.util.*;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;


/**
 * A sequence of air pollution measurements.
 *
 * <p>Created for COMP1721 Coursework 1.</p>
 *
 * @author JONATHAN ALDERSON
 */
public class PollutionDataset{

  private LinkedList<Measurement> measurements;

  public PollutionDataset() {
     measurements = new LinkedList<>();

  }

  public void readCSV(String filename) throws FileNotFoundException {
    measurements.clear();
    try{
      BufferedReader br = new BufferedReader(new FileReader(filename));
      String line = ""; // Initialising the line string to be empty

      while ((line = br.readLine()) != null)
      {
        try{
          Measurement tempMeasurement = new Measurement(line);
          add(tempMeasurement);

        }
        catch(DataException e){}
      }
    }
    catch(IOException e){
      throw new FileNotFoundException("File has not been found");
    }
  }

  public void add(Measurement m) {
    measurements.addLast(m);
  }

  public int size() {
    return measurements.size(); // setters and getters
  }

  public Measurement get(int index) throws DataException{
    if(index >= size())
    {
      throw new DataException("List index out of range!");
    }
    else
    {
    return measurements.get(index);
  }
  }

  public Measurement maxLevel() {
    int currentMax = 0;
    int currentMaxIndex = -1;
    int currentMeasurement = 0;

    for(int i = 0;i < measurements.size();i++)
    {
      currentMeasurement = measurements.get(i).getLevel();

      if(currentMeasurement > currentMax)
      {
        currentMax = currentMeasurement;
        currentMaxIndex = i;
      }

    }

    if(measurements.size() == 0)
    {
      throw new DataException("Cannot find max value from exmpty data set!");
    }

    return measurements.get(currentMaxIndex);
  }

  public Measurement minLevel() {
    // sets the current min to be high, so that it can be changed later
    int currentMin = 99999999;
    int currentMinIndex = -1;
    int currentMeasurement = 0;
    for(int i = 0;i < measurements.size();i++)
    {
      currentMeasurement = measurements.get(i).getLevel();
      if(currentMeasurement < currentMin && currentMeasurement >= 0)
      {
        currentMin = currentMeasurement;
        currentMinIndex = i;
      }
    }

    if(measurements.size() == 0 || currentMin == 99999999)
    {
      throw new DataException("Cannot find min value from exmpty data set!"); // foolproof
    }

    return measurements.get(currentMinIndex);
  }

  public double meanLevel()
  {
    double totalPollution = 0;
    double totalValidLines = 0;
    int currentMeasurement = 0;

    for(int i = 0;i < measurements.size();i++)
    {
      currentMeasurement = measurements.get(i).getLevel();
      if(currentMeasurement >= 0) // so is valid
      {
        totalPollution += currentMeasurement;
        totalValidLines += 1;
      }
    }
    if(totalValidLines == 0)
    {
      throw new DataException("No Valid Lines To Form Average!");
    }
    return(totalPollution / totalValidLines); // cheeky one liner
  }

  public LocalDate dayRulesBreached()
  {
    double totalPollution = 0;
    int hourlyPollution = 0;
    double totalValidLines = 0;
    int currentMeasurement = 0;
    LocalDateTime breachTime = null;
    int numberOfBreaches = 0;

    if(measurements.size() == 0)
    {
      throw new DataException("Cannot Find Breach From Empty Set!");
    }
    for(int i = 0;i < measurements.size()-10;i+=4)
    {
      hourlyPollution = 0;

      for(int j = 0; j< 4; j++)
      {
        currentMeasurement = measurements.get(i+j).getLevel();
        if(currentMeasurement >= 0) // so is valid
        {
          hourlyPollution += currentMeasurement;
        }
      }
      if(hourlyPollution > 200) // since 200 * 4 = 800
      {
        breachTime = measurements.get(i).getTime();
        numberOfBreaches ++;
        if(numberOfBreaches == 18) // the limit of breaches for the law
        {
          return(breachTime.toLocalDate());
        }

      }
    }
    return null;
  }

}
