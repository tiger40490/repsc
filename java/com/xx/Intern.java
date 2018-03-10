package com.xx;
import java.lang.System.out;

public class Intern {
    public static void main(String[] args) {
        String s1 = "Test";
        String s2 = "Test";
        String s3 = new String("Test");
        final String s4 = s3.intern();
        System.out.println(s1 == s2); //true 2 literals
        System.out.println(s2 == s3); //false by default, no intern
        System.out.println(s3 == s4); //false ? 
        System.out.println(s1 == s4); //true thanks to intern()
    }
}
