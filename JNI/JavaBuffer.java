import java.nio.ByteBuffer;

public class JavaBuffer {
    static {
        System.loadLibrary("nativeLibrary"); // Load the JNI library
    }

    private native void processBuffer(ByteBuffer buffer);

    public static void main(String[] args) {
        ByteBuffer buffer = ByteBuffer.allocateDirect(1024); // Allocate a direct byte buffer
        buffer.putInt(42); // Populate the buffer with some data

        System.out.println(System.currentTimeMillis());

        JavaBuffer javaBuffer = new JavaBuffer();
        javaBuffer.processBuffer(buffer); // Call the JNI method to process the buffer

        buffer.flip(); // Reset the buffer position and limit

        int value = buffer.getInt(); // Retrieve the updated data from the buffer
        System.out.println(System.currentTimeMillis());
        System.out.println("Updated value: " + value);
    }
}
