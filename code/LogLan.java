// Code which demonstrates the use of Java's regular expression libraries.
// This is a solution for 
//
//   Loglan: a logical language
//   http://acm.uva.es/p/v1/134.html
//
// In this problem, we are given a regular language, whose rules can be
// inferred directly from the code.  For each sentence in the input, we must
// determine whether the sentence matches the regular expression or not.  The
// code consists of (1) building the regular expression (which is fairly
// complex) and (2) using the regex to match sentences.

import java.util.*;
import java.util.regex.*;

public class LogLan {

    public static String BuildRegex (){
	String space = " +";

	String A = "([aeiou])";
	String C = "([a-z&&[^aeiou]])";
	String MOD = "(g" + A + ")";
	String BA = "(b" + A + ")";
	String DA = "(d" + A + ")";
	String LA = "(l" + A + ")";
	String NAM = "([a-z]*" + C + ")";
	String PREDA = "(" + C + C + A + C + A + "|" + C + A + C + C + A + ")";

	String predstring = "(" + PREDA + "(" + space + PREDA + ")*)";
	String predname = "(" + LA + space + predstring + "|" + NAM + ")";
	String preds = "(" + predstring + "(" + space + A + space + predstring + ")*)";
	String predclaim = "(" + predname + space + BA + space + preds + "|" + DA + space +
            preds + ")";
	String verbpred = "(" + MOD + space + predstring + ")";
	String statement = "(" + predname + space + verbpred + space + predname + "|" + 
            predname + space + verbpred + ")";
	String sentence = "(" + statement + "|" + predclaim + ")";

	return "^" + sentence + "$";
    }

    public static void main (String args[]){

	String regex = BuildRegex();
	Pattern pattern = Pattern.compile (regex);
	
	Scanner s = new Scanner(System.in);
	while (true) {

            // In this problem, each sentence consists of multiple lines, where the last 
	    // line is terminated by a period.  The code below reads lines until
	    // encountering a line whose final character is a '.'.  Note the use of
            //
            //    s.length() to get length of string
            //    s.charAt() to extract characters from a Java string
            //    s.trim() to remove whitespace from the beginning and end of Java string
            //
            // Other useful String manipulation methods include
            //
            //    s.compareTo(t) < 0 if s < t, lexicographically
            //    s.indexOf("apple") returns index of first occurrence of "apple" in s
            //    s.lastIndexOf("apple") returns index of last occurrence of "apple" in s
            //    s.replace(c,d) replaces occurrences of character c with d
            //    s.startsWith("apple) returns (s.indexOf("apple") == 0)
            //    s.toLowerCase() / s.toUpperCase() returns a new lower/uppercased string
            //
            //    Integer.parseInt(s) converts s to an integer (32-bit)
            //    Long.parseLong(s) converts s to a long (64-bit)
            //    Double.parseDouble(s) converts s to a double
            
	    String sentence = "";
	    while (true){
		sentence = (sentence + " " + s.nextLine()).trim();
		if (sentence.equals("#")) return;
		if (sentence.charAt(sentence.length()-1) == '.') break;		
	    }

            // now, we remove the period, and match the regular expression

            String removed_period = sentence.substring(0, sentence.length()-1).trim();
	    if (pattern.matcher (removed_period).find()){
		System.out.println ("Good");
	    } else {
		System.out.println ("Bad!");
	    }
	}
    }
}
