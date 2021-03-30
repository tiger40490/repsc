/*
1 always means Reversed i.e. left-handed.
0 always means Normal i.e. right-handed

I think return value (1 or 0) describes the BEFORE state.

Tested on office Win10 PC, without admin rights. 
*/
using System.Runtime.InteropServices;
using System;

class SwapMouse{
    [DllImport("user32.dll")]
    public static extern Int32 SwapMouseButton(Int32 bSwap);

    static void Main(string[] args)    {
        int ret=999;
        if (args.Length > 0 ){
          if       (String.Compare(args[0], "1") == 0) {
             ret = SwapMouseButton(1);
          }else if (String.Compare(args[0], "0") == 0){
             ret = SwapMouseButton(0);
          }
        }else{ // toggle
          int wasLeftHanded = SwapMouseButton(1); //Make-Reversed
          if (wasLeftHanded != 0){
            wasLeftHanded = SwapMouseButton(0);  //Normalize i.e. Make the left mousebutton primary
          }
          ret = wasLeftHanded;
        }
        Console.WriteLine(ret + " = ret. Hit any key to terminate this applet..");
        Console.Read(); // poor man's pop-up 
    }
}
/*
Req 1: toggle if no-args
Req 2: set to Right-handed if arg is 0
Req 3: set to Left-handed if arg is 1
*/