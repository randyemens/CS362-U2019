package tests;
import java.io.*; 
import java.util.Scanner;
public class UrlValidatorUnitTests {

	public int testCount;
	public int passedCount;
	public String assertPassed(String URL, UrlValidator urlVal, boolean Valid) {
		if (urlVal.isValid(URL) == Valid)
		{
			return "PASSED";
		}
		return "FAILED";
	}
	
	public void runTests(String fileName, UrlValidator urlVal, boolean Valid, UrlValidatorUnitTests tests) {
		try {
		    Scanner urlFile = new Scanner(new File(fileName));
			String nextURL = null;
			while (urlFile.hasNextLine()) {
				nextURL = urlFile.nextLine();
		    	System.out.println(nextURL + ": " + assertPassed(nextURL, urlVal, Valid));
		    	if (assertPassed(nextURL, urlVal, Valid) == "PASSED")
		    	{
			    	tests.passedCount++;
		    	}
		    	tests.testCount++;
			}
			urlFile.close();
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
	    UrlValidatorUnitTests tests = new UrlValidatorUnitTests();
	    UrlValidator urlValidator = new UrlValidator();
	    System.out.println("\n-----------------------------------------------------");
	    System.out.println("DEFAULT URL TESTS");
	    System.out.println("-----------------------------------------------------");
	    System.out.println("Valid URLs:");
	    tests.runTests("test_DEFAULT_VALID.txt", urlValidator, true, tests);
	    System.out.println("\nInvalid URLs:");
	    tests.runTests("test_DEFAULT_INVALID.txt", urlValidator, false, tests);
	    System.out.println("\n-----------------------------------------------------");
	    System.out.println("LOCAL URL TESTS");
	    System.out.println("-----------------------------------------------------");
	    urlValidator = new UrlValidator(UrlValidator.ALLOW_LOCAL_URLS);
	    System.out.println("Valid URLs:");
	    tests.runTests("test_LOCAL_VALID.txt", urlValidator, true, tests);
	    System.out.println("\nInvalid URLs:");
	    tests.runTests("test_LOCAL_INVALID.txt", urlValidator, false, tests);
	    System.out.println("\n-----------------------------------------------------");
	    System.out.println("ALLOW 2 SLASH URL TESTS");
	    System.out.println("-----------------------------------------------------");
	    urlValidator = new UrlValidator(UrlValidator.ALLOW_2_SLASHES);
	    System.out.println("Valid URLs:");
	    tests.runTests("test_2SLASHES_VALID.txt", urlValidator, true, tests);
	    System.out.println("\nInvalid URLs:");
	    tests.runTests("test_2SLASHES_INVALID.txt", urlValidator, false, tests);
	    System.out.println("\n-----------------------------------------------------");
	    System.out.println("NO FRAGMENT URL TESTS");
	    System.out.println("-----------------------------------------------------");
	    urlValidator = new UrlValidator(UrlValidator.NO_FRAGMENTS);
	    System.out.println("Valid URLs:");
	    tests.runTests("test_NOFRAG_VALID.txt", urlValidator, true, tests);
	    System.out.println("\nInvalid URLs:");
	    tests.runTests("test_NOFRAG_INVALID.txt", urlValidator, false, tests);
	    System.out.println("\n-----------------------------------------------------");
	    System.out.println("SCHEMES URL TESTS");
	    System.out.println("-----------------------------------------------------");
	    String[] testSchemes = {"test","valid","schemes"};
	    urlValidator = new UrlValidator(testSchemes);
	    System.out.println("Valid URLs:");
	    tests.runTests("test_SCHEMES_VALID.txt", urlValidator, true, tests);
	    System.out.println("\nInvalid URLs:");
	    tests.runTests("test_SCHEMES_INVALID.txt", urlValidator, false, tests);
	    System.out.println("-----------------------------------------------------");
	    System.out.println("Tests Passed: " + tests.passedCount +" out of " + tests.testCount);
	    System.out.println("-----------------------------------------------------");
	}

}
