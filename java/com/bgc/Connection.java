package com.bgc;

import com.bgc.Graph.Builder;

public class Connection {
	public static void main(String[] args) {
		Graph inst = new Builder().withArray(args).build();
		//System.out.println(inst.fileName);
		System.out.println(inst.cityName1 + " / " + inst.cityName2 + " connected? " 
		+ inst.checkTheConnection());
	}
}
