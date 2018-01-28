package com.gelber;

import java.io.InputStreamReader;
import java.io.LineNumberReader;
import java.io.OutputStream;
import java.io.Reader;
import java.net.Socket;

public class Downloader {
	static Reader download(String webServer, String location){
		LineNumberReader reader = null;
		try {
			Socket sock = new Socket(webServer, 80);
			OutputStream ostream = sock.getOutputStream();
			ostream.write(("GET " + location + "\n\n").getBytes());
			ostream.flush();
			reader = new LineNumberReader(new InputStreamReader(
					sock.getInputStream()));
		} catch (Exception e) {
			e.printStackTrace();
		}
		return reader;
	}
}
