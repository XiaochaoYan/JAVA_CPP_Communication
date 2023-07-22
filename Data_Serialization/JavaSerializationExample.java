import java.io.IOException;
import com.fasterxml.jackson.databind.ObjectMapper;
import java.nio.file.Paths;

public class JavaSerializationExample {

    // Static nested class representing the data to be serialized
    static class JavaObjectData {
        private int value;
        private String message;

        public JavaObjectData() {
            // Default constructor required for Jackson serialization
        }

        public JavaObjectData(int value, String message) {
            this.value = value;
            this.message = message;
        }

        // Getters and setters (required for Jackson serialization)
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

        // Serialization method
        public void serialize(String fileName) throws IOException {
            ObjectMapper objectMapper = new ObjectMapper();
            objectMapper.writeValue(Paths.get(fileName).toFile(), this);
        }
    }

    public static void main(String[] args) {
        JavaObjectData data = new JavaObjectData(42, "Hello from Java!");
        try {
            data.serialize("data.json");
            System.out.println("Data serialized successfully.");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
