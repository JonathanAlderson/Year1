// Correctness testing for COMP1721 Coursework 1 (Basic Solution)

import java.io.FileNotFoundException;
import java.time.LocalDateTime;

import org.junit.Before;
import org.junit.Test;
import org.junit.runner.JUnitCore;
import org.junit.runner.Result;

import static org.hamcrest.Matchers.*;
import static org.hamcrest.MatcherAssert.*;


public class BasicTests {

  private Measurement m1, m2, m3, m4;
  private PollutionDataset empty, dataset;

  @Before
  public void perTestSetup() {
    m1 = new Measurement("30/01/2018,00:15,42");
    m2 = new Measurement("30/01/2018,00:30,");
    m3 = new Measurement("30/01/2018,00:45,0");
    m4 = new Measurement("30/01/2018,01:00,6");

    empty = new PollutionDataset();
    dataset = new PollutionDataset();
    dataset.add(m1);
    dataset.add(m2);
    dataset.add(m3);
    dataset.add(m4);
  }

  // Measurement class

  @Test
  public void time() {
    assertThat(m1.getTime(), is(LocalDateTime.of(2018, 1, 30, 0, 15)));
    assertThat(m2.getTime(), is(LocalDateTime.of(2018, 1, 30, 0, 30)));
  }

  @Test
  public void level() {
    assertThat(m1.getLevel(), is(42));
    assertThat(m2.getLevel(), is(-1));
    assertThat(m3.getLevel(), is(0));
  }

  @Test
  public void measurementAsString() {
    assertThat(m1.toString(), is("2018-01-30T00:15, 42 \u00b5g/m\u00b3"));
    assertThat(m2.toString(), is("2018-01-30T00:30, no data"));
    assertThat(m3.toString(), is("2018-01-30T00:45, 0 \u00b5g/m\u00b3"));
  }

  @Test(expected=DataException.class)
  public void emptyRecord() {
    new Measurement("");
  }

  @Test(expected=DataException.class)
  public void oneItemInRecord() {
    new Measurement("30/01/2018");
  }

  @Test(expected=DataException.class)
  public void fourItemsInRecord() {
    new Measurement("30/01/2018,00:15,42,0");
  }

  // PollutionDataset class

  @Test
  public void datasetSize() {
    assertThat(empty.size(), is(0));
    assertThat(dataset.size(), is(4));
  }

  @Test
  public void getMeasurement() {
    assertThat(dataset.get(0), is(m1));
    assertThat(dataset.get(1), is(m2));
    assertThat(dataset.get(2), is(m3));
    assertThat(dataset.get(3), is(m4));
  }

  @Test(expected=DataException.class)
  public void getMeasurementEmptyDataset() {
    empty.get(0);
  }

  @Test
  public void maxLevel() {
    assertThat(dataset.maxLevel(), is(m1));
  }

  @Test(expected=DataException.class)
  public void maxLevelEmptyDataset() {
    empty.maxLevel();
  }

  @Test(expected=FileNotFoundException.class)
  public void readCSVFileNotFound() throws FileNotFoundException {
    dataset.readCSV("this_file_does_not_exist.csv");
  }

  @Test
  public void readCSV() throws FileNotFoundException {
    dataset.readCSV("../data/test.csv");
    assertThat(dataset.size(), is(8));
  }

  // main

  public static void main(String[] args) {
    JUnitCore core = new JUnitCore();
    core.addListener(new TestReporter());
    Result result = core.run(BasicTests.class);
    System.exit(result.getFailureCount());
  }
}
