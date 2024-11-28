import serial
import time

# Configure the serial connection
# Replace 'COM3' with the port name your Arduino is connected to
ser = serial.Serial('COM3', 9600, timeout=1)
line = ""
line2 = ""

output_file = "random_numbers.txt"  # Output file to store the generated numbers

try:
    print("Please wait for random numbers to be generated (Ctrl+C to exit).")
    with open(output_file, "a") as file:  # Open file in append mode
        for i in range(500 * 2):  # Random numbers to generate
            time.sleep(0.05)  # Sleep for stability
            char = ser.read().decode('utf-8').strip()  # Read a character from the serial port
            if char:  # Only process non-empty characters
                line2 += char
                if len(line2) % 2 == 0:  # Insert a comma after every second character
                    line += char + ","
        file.write(line.rstrip(","))  # Append to file, removing trailing comma
    print("Numbers written to", output_file)
except KeyboardInterrupt:
    print("\nExiting...")
finally:
    ser.close()
