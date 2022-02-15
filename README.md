*A quick description of how my code works:*
 
 
 
The code is relatively well commented so feel free to poke around it...
 
Essentially my code just translates what I was doing when I was making the adjacency matrix and taking the rank of it myself.
 
Initially, it asks the user for the biggest board they’d like to analyze. Then starting at a 2x2 board it does the following for each board size.
 
First it builds a “gameboard” which is labeled in the same manner we have been labeling it this whole project, with square #1 in the top left corner, #2, in the next square in the first row, etc.
 
E.g. for the 3x3 case, it builds a matrix that looks like this:
 
|1| |2| |3|
----------
|4| |5| |6|
 
After building this matrix, it systematically goes through each square in the “gameboard” checking which of the following category that square falls under:
 
·      Top right, top left, bottom right, or bottom left corner piece.
·      A “boarder” piece, and if it is a top boarder piece, left boarder piece, bottom boarder piece, or right boarder piece.
·      A “center” like square. (Though this doesn’t have to be the center square, just any square that isn’t the above 2.)
 
Which lights toggle these categories of squares are the same… e.g. for a “center” square the following will toggle it:
            The square number – boardsize
            The square number – 1
            The square number
            The square number +1
            The squar number + boardsize.
 
Similar analyses can be done for the other categories.
 
It then goes through the board checking each box number to see if it is one of these “important” numbers that effects the square we are currently analyzing. It adds a 1 to a vector if it finds one, otherwise it just adds 0. Finally it adds that vector to the adjacency matrix.
 
 
Since were working modulo 2 a row reduction algorithm is relatively simple, I build a RowReduce function and put the adjacency matrix the program built in rref.
 
Then it counts the rank of that matrix by simply checking for 1’s in locations where the row number = the column number.

Note the binary included is for an M1 Mac, but feel free to compile for your own platform. (Only has been tested with clang compiler, however any should work.)
