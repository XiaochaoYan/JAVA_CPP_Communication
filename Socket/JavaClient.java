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
            writer.println("Hello from Java! " + System.currentTimeMillis() + "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");

            // Close the streams and socket
            writer.close();
            outputStream.close();
            socket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
