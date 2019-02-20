# ImageServer
This program allows two IP addresses on the same network to send images to each other. 

Use Linux to run

1. Compile both the server and client cpp file
g++ server.cpp -o imageServer
g++ client.cpp -o imageClient

2. Make sure the port numbers are the same and which IP address you are on.
Ready two image files to be sent.

3. Run both of the Unix Executable in two different windows.
./imageServer <port num> <file name1> <file name2>

./imageClient <IP address> <port num> <image num> <to save filename>
