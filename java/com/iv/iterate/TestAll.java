package com.iv.iterate;

import org.junit.runner.RunWith;
import org.junit.runners.Suite;

@RunWith(Suite.class)

@Suite.SuiteClasses({
	TestFilterIteratorSingleThreaded.class, 
	TestConcurrentFilterIterator.class,
	TestConcurrentNonFilterIterator.class}
)

public class TestAll { //v1.0
}