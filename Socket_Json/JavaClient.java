import java.io.*;
import java.net.*;
import com.fasterxml.jackson.databind.ObjectMapper;

public class JavaClient {
    public static void main(String[] args) {
        int numIterations = 10000; // Number of iterations for benchmark
        long totalTime = 0;

        for (int i = 0; i < numIterations; i++) {
            try (Socket socket = new Socket("localhost", 1234);
                 OutputStream out = socket.getOutputStream();
                 BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()))) {

                // Create a Java object to serialize as JSON
                JavaObjectData data = new JavaObjectData(42, "Hello from Java!");

                // Convert the Java object to JSON
                ObjectMapper objectMapper = new ObjectMapper();
                String jsonData = objectMapper.writeValueAsString(data);

                // Send the JSON data to the C++ server
                long startTime = System.currentTimeMillis();
                out.write(jsonData.getBytes());
                out.flush();

                // Read response from the server
                String response = in.readLine();
                long endTime = System.currentTimeMillis();

                System.out.println("Received from C++ server: " + response);

                long iterationTime = endTime - startTime;
                totalTime += iterationTime;
                System.out.println("Iteration time: " + iterationTime + " ms");
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

        // Calculate and print benchmark statistics
        long averageTime = totalTime / numIterations;
        System.out.println("\nBenchmark Statistics:");
        System.out.println("Total time taken for " + numIterations + " iterations: " + totalTime + " ms");
        System.out.println("Average time per iteration: " + averageTime + " ms");
    }
}

class JavaObjectData {
    private int value;
    private String message;

    public JavaObjectData(int value, String message) {
        this.value = value;
        this.message = message;
    }

    public int getValue() {
        return value;
    }

    public void setValue(int value) {
        this.value = value;
    }

    public String getMessage() {
        return message;
    }

    public void setMessage(String message) {
        this.message = message;
    }

    // Getters and setters (you can generate them automatically)
}
