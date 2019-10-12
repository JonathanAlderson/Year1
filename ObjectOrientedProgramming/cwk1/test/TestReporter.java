// Correctness testing for COMP1721 Coursework 1

import org.junit.runner.Result;
import org.junit.runner.notification.Failure;
import org.junit.runner.notification.RunListener;


public class TestReporter extends RunListener {

  @Override
  public void testRunFinished(Result result) {
    printSummary(result);
    if (result.getFailureCount() > 0) {
      printFailureInfo(result);
    }
  }

  private void printSummary(Result result) {

    int testsFailed = result.getFailureCount();
    int testsPassed = result.getRunCount() - testsFailed;

    if (testsPassed == 1) {
      System.out.print("1 test passed");
    }
    else {
      System.out.printf("%d tests passed", testsPassed);
    }

    if (testsFailed > 1) {
      System.out.printf(", %d tests failed%n", testsFailed);
    }
    else if (testsFailed == 1) {
      System.out.println(", 1 test failed");
    }
    else {
      System.out.println();
    }
  }

  private void printFailureInfo(Result result) {

    System.out.println("\nDetails of failures:");

    int n = 1;
    for (Failure fail: result.getFailures()) {

      System.out.printf("%n(%d) %s:%n", n, fail.getTestHeader());

      Throwable error = fail.getException();
      StackTraceElement[] trace = error.getStackTrace();

      if (error instanceof AssertionError) {
        // This was a failed test, so find the assertion that failed
        System.out.println("Assertion failed");
        System.out.println(fail.getMessage().trim());
        for (StackTraceElement e: trace) {
          String text = String.format("%s(%s)", e.getMethodName(), e.getClassName());
          if (text.equals(fail.getDescription().toString())) {
            System.out.printf("(See line %d of %s)%n",
              e.getLineNumber(), e.getFileName());
            break;
          }
        }
      }
      else {
        // Test was prevented from running properly
        System.out.printf("%s (%s:%d)%n",
          error, trace[0].getFileName(), trace[0].getLineNumber());
      }

      ++n;
    }
  }
}
