package com.xx;
import java.lang.System;

public class Intern {
    public static void main(String[] args) {
        String literal1 = "Test";
        String literal2 = "Test";
        String s3 = new String("Test"); // different object
        final String internalized = s3.intern(); // returns a reference of the literal
		// results in Java 8:
        System.out.println(literal2 == literal1); //true 2 literals
        System.out.println(literal2 == internalized); //true interned object IS the s2 object
        System.out.println(s3 == literal2 ); //false by default, no intern
        System.out.println(s3 == internalized); //false !!!!!!!
    }
}
