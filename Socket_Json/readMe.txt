javac -cp "lib/*" JavaClient.java

g++ -std=c++11 -I"include" CppServer.cpp -o CppServer.exe -lws2_32


./CppServer.exe

java -cp "lib/*" JavaClient.java
