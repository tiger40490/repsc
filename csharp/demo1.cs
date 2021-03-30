using System;
public class Program{
    public static void Main(string [] args){
        Console.WriteLine("Hello world");
    }
}
/* based on https://abundantcode.com/how-to-run-the-c-program-from-commandline-using-csc-exe/

PATH=$PATH:/C/Windows/Microsoft.NET/Framework/v4.0.30319/

csc.exe //nologo //out:a.exe demo1.cs && ./a.exe

*/