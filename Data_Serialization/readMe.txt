javac -cp "lib/*" JavaObjectData.java
javac -cp "lib/*" JavaSerializationExample.java

java -cp "lib/*" JavaSerializationExample.java

g++ -std=c++11 -I"include" CppDeserialization.cpp -o CppDeserialization.exe