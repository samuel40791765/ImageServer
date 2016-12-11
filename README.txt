{\rtf1\ansi\ansicpg1252\cocoartf1404\cocoasubrtf470
{\fonttbl\f0\fswiss\fcharset0 Helvetica;}
{\colortbl;\red255\green255\blue255;}
\paperw11900\paperh16840\margl1440\margr1440\vieww10800\viewh8400\viewkind0
\pard\tx566\tx1133\tx1700\tx2267\tx2834\tx3401\tx3968\tx4535\tx5102\tx5669\tx6236\tx6803\pardirnatural\partightenfactor0

\f0\fs24 \cf0 Use Linux to run\
\
1. Compile both the server and client cpp file\
	g++ server.cpp -o imageServer\
	g++ client.cpp -o imageClient\
\
2. Make sure the port numbers are the same and which IP address you are on.\
	Ready two image files to be sent.\
\
3. Run both of the Unix Executable in two different windows.\
	./imageServer <port num> <file name1> <file name2>\
\
	./imageClient <IP address> <port num> <image num> <to save filename>\
\
}