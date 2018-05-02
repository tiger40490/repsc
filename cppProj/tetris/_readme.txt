--how to run--
In Linux, run.sh is the simplest.

I also ran main.cpp in Eclipse using gcc in Windows XP. It's a simple project so compilation should be straightforward. After the build, there should be an executable object file.

Each line in data/input.txt is an independent test. Each line in data/output.txt has one number which is the height of the pile at end of each test.

I included my console output in ./data/_console_output.log, showing the visualization mentioned below. You should get the same console output.

--assumptions--
Assumption : "Steam bubbles immediately become ice cubes."

Let me try to explain. Whenever a "void" space gets covered from above, "steam" is trapped in a bubble and becomes ice cube. The voed is considered ice-filled, permanently. (It remains filled with ice cube, even if the piece above gets removed later.)

The drawRotated() function makes it much easier and intuitive to visualize the ice cubes.

--data structures--
The board -- matrix of Cells. 

A Cell -- knows the identity of the occupying "host piece" and its shape. This enables meaningful visualization of whole pieces on a crowded Board.

The shapes -- each a collection of 4 Square objects. All 7 shapes are instances of the same class.

A Square -- has a x/y coordniate relative to the anchor position of the host shape. 

--visualization--
The drawRotated() gives a simple and fairly complete picture of the Board at any time. The shadows/ice cubes are a bit tricky without visualization.

There are some nice little features to ease the visualization. Each Square is always "painted" using 2 characters -- an id and a shape-character. The shape-character is either a lower or upper case of the original shape.  The id can be 1/2/3/4/5 or a meta-character. Together, they help the human eye make out whole pieces on a crowaded board.

