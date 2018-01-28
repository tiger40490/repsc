package com.hsbc.slidingWindow;

/**
 * I don't prefer to use float alone. Could lose precision if the original input 
 * is an integer data type.
 * 
 * I don't prefer int (or long) along because the range is too limited. 
 * 
 * Therefore, this interface provides 2 options. Each subtype will usually choose 
 * one of the types to implement, leaving the other method to the default, provided
 * by the AbstractMeasurement class.
 *
 */
public interface Measurement { //v1.0
	double floatValue();
	int intValue();
}
