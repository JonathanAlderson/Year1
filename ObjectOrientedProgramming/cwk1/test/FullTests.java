// Class correctness testing for COMP1721 Coursework 1 (Full Solution)

import java.io.FileNotFoundException;
import java.time.LocalDate;

import org.junit.Before;
import org.junit.Test;
import org.junit.runner.JUnitCore;
import org.junit.runner.Result;

import static org.hamcrest.Matchers.*;
import static org.hamcrest.MatcherAssert.*;


public class FullTests {

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

  @Test
  public void minLevel() {
    assertThat(dataset.minLevel(), is(m3));
  }

  @Test(expected=DataException.class)
  public void minLevelEmptyDataset() {
    empty.minLevel();
  }

  @Test
  public void meanLevel() {
    assertThat(dataset.meanLevel(), closeTo(16.0, 0.000001));
  }

  @Test(expected=DataException.class)
  public void meanLevelEmptyDataset() {
    empty.meanLevel();
  }

  @Test
  public void dayBreached() throws FileNotFoundException {
    PollutionDataset data = new PollutionDataset();
    data.readCSV("../data/kirkstall.csv");
    assertThat(data.dayRulesBreached(), is(LocalDate.of(2016, 1, 4)));
  }

  @Test
  public void dayBreachedNullResult() {
    PollutionDataset data = new PollutionDataset();
    data.add(new Measurement("30/01/2018,00:15,22"));
    data.add(new Measurement("30/01/2018,00:30,45"));
    data.add(new Measurement("30/01/2018,00:45,50"));
    data.add(new Measurement("30/01/2018,01:00,63"));
    assertThat(data.dayRulesBreached(), is(nullValue()));
  }

  @Test(expected=DataException.class)
  public void dayBreachedEmptyDataset() {
    empty.dayRulesBreached();
  }

  public static void main(String[] args) {
    JUnitCore core = new JUnitCore();
    core.addListener(new TestReporter());
    Result result = core.run(FullTests.class);
    System.exit(result.getFailureCount());
  }
}
