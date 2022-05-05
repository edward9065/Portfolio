# Portfolio
A quick portfolio of some of my code

<h3> Two-Way Chat </h3>
<p>
May not work in windows due to missing header files.

Two way chat between a client and a server run in the command line. Running the executable without providing any additional arguments starts the program in "server mode." The server begins by randomly selecting an ephemeral-range port. It then displays the IP address and port number to the terminal. Then, it listens for IPv4 connections on any IP address and accepts the client's socket once. 

Running the executable followed by two arguments, the IP address and port given previously by the server, starts the program in "client mode." It the connects to the given IP address and port.

Both programs use poll in an infinite loop to pick either the connected socket or standard in to read from. If it reads from the connected socket, it writes to the standard out. If it reads from standard in, it writes to the socket.

Included is a demo tested on UVA's CS department servers. I compile and run it here: </p>

https://user-images.githubusercontent.com/96403210/166975620-9b7d8065-05d0-4232-ac7c-0be17e10b40a.mp4

<h3> RPN Calculator </h3>
<p>
May not work in windows due to missing header files.

Reverse polish notation calculator that takes input from standard in, parses it, and calculates the result. The program can recognize any signed 32-bit integer and these four operators: "+", "-", "*", "/". The calculator prints out the intermediate stacks as as it runs. 
  
The program terminates when it encounters an unrecognized token, reaches the end of input, or does not have enough operands to perform an operation. The program can handle extremely long lines as well as multiple short lines. 

Below is a demo of the calculator which was compiled and run on UVA's CS department servers:

Suggested test cases: large integers, many integers and operations, and multiple whitespaces between tokens. End of input can be done by pressing Cntl+D. In addition, the command "echo -n 12 2 3 * 2 + | ./rpn" can be used to test the calculator's function if the input is ended without a newline character.

Below is a demo of the calculator which was compiled and run on UVA's CS department servers:
</p>

https://user-images.githubusercontent.com/96403210/166978520-3ece8755-31f2-4671-a133-fe7ca23e96c4.mp4


