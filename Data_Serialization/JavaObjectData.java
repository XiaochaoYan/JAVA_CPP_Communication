import com.fasterxml.jackson.databind.ObjectMapper;
import java.io.IOException;
import java.nio.file.Paths;

class JavaObjectData {
    private int value;
    private String message;

    public JavaObjectData(int value, String message) {
        this.value = value;
        this.message = message;
    }

    // Getters and setters (you can generate them automatically)

    // Serialization method
    public void serialize(String fileName) throws IOException {
        ObjectMapper objectMapper = new ObjectMapper();
        objectMapper.writeValue(Paths.get(fileName).toFile(), this);
    }
}
