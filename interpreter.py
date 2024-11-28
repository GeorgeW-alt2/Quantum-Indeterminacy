import serial
import time
# Configure the serial connection
# Replace 'COM3' with the port name your Arduino is connected to
ser = serial.Serial('COM3', 9600, timeout=1)
line = ""
try:
    print("Please wait for the numbers to be generated (Ctrl+C to exit).")
    for i in range(100*2): #random numbers to generate
        time.sleep(0.05) # sleep for stability
        line += ser.read().decode('utf-8').strip()  # Read a line from the serial port
    print(line)  # Display the number
except KeyboardInterrupt:
    print("\nExiting...")
finally:
    ser.close()
