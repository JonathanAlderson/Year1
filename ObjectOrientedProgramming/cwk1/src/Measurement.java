import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

/**
 * A single measurement of NO<sub>2</sub> level.
 *
 * <p>Created for COMP1721 Coursework 1.</p>
 *
 * @author JONATHAN ALDERSON
 */
public class Measurement {
  // Use this when parsing measurement time
  private static DateTimeFormatter FORMAT = DateTimeFormatter.ofPattern("dd/MM/yyyy HH:mm");
  private LocalDateTime time;
  private int level;

  public Measurement(String record) {

    level = -1;  // Default value
    String[] splitRecord = record.split(",");

    if(splitRecord.length == 3 || splitRecord.length == 2) // Definitely has a time we can use
    {
      String dateString = splitRecord[0] +" "+ splitRecord[1];
      try
      {
      time = LocalDateTime.parse(dateString, FORMAT); // parsing the time so that it is put into the correct format
      }
      catch(java.time.format.DateTimeParseException e)
      {
        throw new DataException("Invalid Parsing Format!");
      }

    }

    if(splitRecord.length == 3)   // Has a level to use
    {
      level = Integer.parseInt(splitRecord[2]);
    }

    if(splitRecord.length > 3 || splitRecord.length < 2)  // Is invalid
    {
      throw new DataException("Error Invalid Record Formatting!"); // another helpful user message
    }

  }

  public LocalDateTime getTime() {
    return time;
  }

  public int getLevel() {
    return level;
  }

  public String toString() {
    String returnString = "no time, no data";  // Default sring
    if(level != -1)
    {
      returnString = time + ", " + level + " \u00b5g/m\u00b3"; // correct formatting for the Co2 level
    }
    else
    {
      if(time != null)
      {
      returnString = time + ", no data";  // case where you have he time but no data
      }
    }
    return returnString;
  }
}
