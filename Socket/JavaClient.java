import java.io.*;
import java.net.*;

public class JavaClient {
    public static void main(String[] args) {
        try {
            // Connect to the server
            Socket socket = new Socket("localhost", 1234);

            // Get the output stream to send data to the server
            OutputStream outputStream = socket.getOutputStream();
            PrintWriter writer = new PrintWriter(outputStream, true);

            // Send data to the server
            writer.println("Hello from Java! " + System.currentTimeMillis());

            // Close the streams and socket
            writer.close();
            outputStream.close();
            socket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
