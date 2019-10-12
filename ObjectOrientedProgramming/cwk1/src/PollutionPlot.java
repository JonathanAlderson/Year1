
//java FX Imports
import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.chart.LineChart;
import javafx.scene.chart.NumberAxis;
import javafx.scene.chart.XYChart;
import javafx.stage.Stage;
import java.io.*;
import java.util.Scanner;
import java.util.concurrent.TimeUnit;
import java.lang.Math;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;


public class PollutionPlot extends Application {

  @Override
  public void start(Stage stage) {
    final NumberAxis xAxis = new NumberAxis();
    final NumberAxis yAxis = new NumberAxis();

    final LineChart<Number, Number> lineChart = new LineChart<Number, Number>(
        xAxis, yAxis);

    // Initialising parts of the line graph
    XYChart.Series<Number, Number> series = new XYChart.Series<Number, Number>();
    XYChart.Series<Number, Number> series2 = new XYChart.Series<Number, Number>();


    // String Inputs

    Scanner scanner=new Scanner(System.in);

    System.out.printf("\nDisplays data from a single day from a file.\n\nInput file to read from: ");
    String fileToRead = scanner.nextLine();
    System.out.printf("\nInput year:");
    int year = scanner.nextInt();
    System.out.printf("\nInput month:");
    int month = scanner.nextInt();
    System.out.printf("\nInput day:");
    int day = scanner.nextInt();
    int currentLevel = 0;
    int secondLevel = 0;
    int thirdLevel = 0;
    int fourthLevel = 0;
    int firstPosition = -1;
    LocalDate line;

    // Pollution Dataset information
    series.setName("Every 15 Minutes");
    series2.setName("Every Hour");
    lineChart.setTitle("Air Pollution Levels for file " + fileToRead);
    xAxis.setLabel("Data for " + day + "/" + month + "/"  + year);
    yAxis.setLabel("Pollution of NO2 in µg/m\u00b3");
    PollutionDataset firstDataset =  new PollutionDataset();
    // Tests if file exists and is valid to read
    try
    {
      firstDataset.readCSV(fileToRead);
    }
    catch(FileNotFoundException e)
    {
      System.out.printf("\n\nFile not found\nPlease enter a file, ending with .csv\n\n");
      return;
    }

    for(int i=0;i<firstDataset.size();i++)
    {
      line = firstDataset.get(i).getTime().toLocalDate();
      if(line.getYear() == year && line.getMonthValue() == month && line.getDayOfMonth() == day)
      {
        if(firstPosition == -1)
        {
          firstPosition = i;
        }
        // this is for the every 15 minutes line
        currentLevel = firstDataset.get(i).getLevel();
        secondLevel = firstDataset.get(i+1).getLevel();
        thirdLevel = firstDataset.get(i+2).getLevel();
        fourthLevel = firstDataset.get(i+3).getLevel();
        if(currentLevel > -1)
        {
          series.getData().add(new XYChart.Data<Number, Number>(i-firstPosition,currentLevel));
        }

        if(i%4 == 0)
        {
          if(((currentLevel+secondLevel+thirdLevel+fourthLevel)/4) > -1) // checks that the level is not negative.
          {
            series2.getData().add(new XYChart.Data<Number,Number>(i-firstPosition,((currentLevel+secondLevel+thirdLevel+fourthLevel)/4)));
          }

        }
      }
      if(line.getMonthValue() >= month && line.getYear() >= year && line.getDayOfMonth() > day)
      {
        break; // This checks to see if the current date has already passed, to make the thing more efficient.
      }
    }

    Scene scene = new Scene(lineChart, 800, 600);
    lineChart.getData().add(series);
    lineChart.getData().add(series2);

    // Loads points into javaFX
    stage.setScene(scene);
    stage.show();
    System.out.printf("\n\nShowing Graph.\n\n");


  }

  public static void main(String[] args) {
    launch(args);
  }
}
