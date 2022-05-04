# Portfolio
A quick portfolio of some of my code

<h3> Two-Way Chat </h3>
<p>
May not work in windows due to missing header files.

Two way chat between a client and a server run in the command line. Running the executable without providing any additional arguments starts the program in "server mode." The server begins by randomly selecting an ephemeral-range port. It then displays the IP address and port number to the terminal. Then, it listens for IPv4 connections on any IP address and accepts the client's socket once. 

Running the executable followed by two arguments, the IP address and port given previously by the server, starts the program in "client mode." It the connects to the given IP address and port.

Both programs use poll in an infinite loop to pick either the connected socket or standard in to read from. If it reads from the connected socket, it writes to the standard out. If it reads from standard in, it writes to the socket.

Included is a demo tested on UVA's CS department servers. I compile it to show that it compiles and run it here: </p>


<h3> RPN Calculator </h3>
Only works in linux because windows does not have the required header files.
