import serial

# Configure the serial connection
# Replace 'COM3' with the port name your Arduino is connected to
ser = serial.Serial('COM3', 9600, timeout=1)
line = ""
try:
    print("Press Enter to display the next number (Ctrl+C to exit).")
    while True:
        #input("Press Enter: ")  # Wait for user input
        line += ser.read().decode('utf-8').strip()  # Read a line from the serial port
        print(line)  # Display the number
except KeyboardInterrupt:
    print("\nExiting...")
finally:
    ser.close()
