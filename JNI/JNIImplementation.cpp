#include <jni.h>
extern "C" {
    JNIEXPORT void JNICALL Java_JavaBuffer_processBuffer(JNIEnv* env, jobject obj, jobject buffer) {
        // Get the direct byte buffer address
        jbyte* data = reinterpret_cast<jbyte*>(env->GetDirectBufferAddress(buffer));
        jlong capacity = env->GetDirectBufferCapacity(buffer);

        // Process the buffer data
        for (jlong i = 0; i < capacity; i++) {
            data[i]++; // Increment each byte in the buffer
        }
    }
}