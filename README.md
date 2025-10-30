# Welcome to the OttoBots Coding Section!

Whether you're encountering errors during code upload, seeking to personalize your Otto, or simply exploring the available functions, this guide has got you covered.

I will go over setting up the Arduino IDE, uploading the code and modifying your OttoBot behaviour. We'll primarily focus on two crucial files: `calibration.ino` and `allmoves.ino`. The former is the backbone of your Otto's programming, containing essential setup and loop functions. The latter is a library of Otto functions..

# 1. Setting up the IDE 
Once you have downloaded the [Arduino IDE](https://www.arduino.cc/en/software), open the calibration.ino file.

Now go to library manager (Sketch > Include Library > Manage Libraries) and download **OttoDIYLib** by Otto DIY. Or you can click the library icon on the left of the window. 

<img src="initialise/Library.png" width="auto" height="300px">

To confirm that you have downloaded it, compile the sketch using the 'tick' icon on the top left of the IDE: <img src="initialise/Compile.png" width="500px" height="auto"> 

The code should compile without any errors.

# 2. Uploading to the nano
Once you have completed step 1, connect the otto's Arduino nano to your computer and select the board. The port selection is located at the top of the IDE: 

<img src="initialise/Port.png" width="500px" height="auto">

The IDE might pickup your bluetooth ports like mine has. Usually, the names have "usbserial", "COM52" or similar in it. A trick I use is to disconnect the Arduino, observe which ports are listed, reconnect it, and then identify which new port appears in the list. 

Once you have selected the port and Arduino Nano board, upload the code to the Arduino nano: 

<img src="initialise/Upload.png" width="500px" height="auto">

## Upload Errors
**If you have no errors, you are in luck!**

It's always a mission uploading code using the IDE, here's a fix to a common error that occurs:

<img src="initialise/uploadError.png" width="auto" height="300px"> 

* Run the old bootlegger. Go to Tools > Processor > Atmega328P(Old bootlegger):

  <img src="initialise/oldBootlegger.png" width="auto" height="300px" alt="old bootlegger">

  Now try uploading again, it should work!

* If the same or similar error still persists, ensure the right board and port is selected, press the reset button on the arduino or restart your IDE.

# 3. Serial Monitor
Open the serial monitor to view outputs from the otto. Go to Tools > Serial Monitor to open the monitor. 

<img src="initialise/serialMonitor.png" width="auto" height="300px">

Type in a letter and press enter to send a message to otto!

# 4. Its ALIVE
If you have assembled the otto correctly, the hardware is functional, the wires aren't faulty and the stars align, then your robot should move towards any object it sees within 10cm and home its legs when you send the corresponding message. 

# 5. Modifying your Otto
`Calibration.ino` contains some starter code with a simple object detection function. `allmoves.ino` contains some functions from the OttoDIY library, copy and paste these functions into `calibration.ino`. The function typically follows this signature:
```
  Otto.function(int STEPS, int T, int D);  // Arguments are: steps, time per step (ms), direction (1 for forward)
```
Lets get started on calibrating your OTTO:

Step 1: Upload the calibration.ino code to your OTTO and check the serial monitor. The output should be 
```
14:10:47.966 -> Distance: 
14:10:47.966 -> 34 (or another number)
```
If your distance is constantly 0 or 800 then your Ultrasonic Sensor needs replacing. 

Step 2: Wave your hand <10cm in front of the sensor and watch the OTTO dance, if it is 'wonky' try step 3.

Step 3: put the otto upside down and use keys a/z, s/x, j/n, k/m on your keyboard to 'home' the legs of the OTTO. we want the legs and feet to be straight and perpendicular. 

Step 4: If one of the servos isn't working, check the connection, check if it restricted in movement physically, and if it still doesn't work then the servo needs replacing. 

Once your otto is calibrated, YOU ARE FREE TO CODE AS YOU PLEASE. 

Feel free to import any function you wish and integrate it into the main loop. For example,
* If you want otto to walk backwards when it detects an object, consider changing 
  ```
  Otto.walk(1, 1000, -1);
  ```
  to
  ```
  Otto.walk(1, 1000, 1);
  ```
* If you want otto to moonwalk when it detects an object, replace the walk function with
  ````
  Otto.moonwalker(3, 1000, 25,-1);
  ````
* If you want otto to carry out a function when you send it a message (in this example we make it do the 'crusaito' when I type "shakeit" in the serial monitor)
  ```
   if((Serial.available()) > (0)){
        charRead = Serial.read();
    }
    if((charRead)==('shakeit' )){
        Otto.moonwalker(2, 1000, 20,1);
  }
  ```
* If you want the ottobot to indefinitely walk forward for a second, wait for a second, then walk backwards for a second, add this to the loop function
  ```
   // Walk forward
  Otto.walk(1, 1000, 1);  // Arguments are: steps, time per step, direction (1 for forward)
  delay(1000); // Wait for a second
  Serial.println("Otto is going places");   //print to the serial monitor to track progress
  // Walk backward
  Otto.walk(1, 1000, -1);  // Arguments are: steps, time per step, direction (-1 for backward)
  delay(1000); // Wait for a second
  Serial.println("Otto retreated, life's rough");
  ```

# 6. Troubleshooting
I've listed some common issues that may aid in the debugging process:
* Ensure the component (servo, US) is connected to the correct pin defined in the code. For example, `#define TRIG_PIN 8` means that the trig pin from your ultrasonic sensor should be connected to pin 8 in the Arduino Nano.
* If the code uploads but the otto has slow or no movements, try replacing the wire.
* If you are using Windows and have issues uploading the code to the nano, search for **CH340 driver download** on your browser and follow the prompts. Since we use arduino nano clones, the necessary drivers might not be installed.

# 7. Conclusion
There is a lot of information online about otto, if you want to upgrade it check out [OttoDIY](https://www.ottodiy.com/academy) for more!

I hope you found this tutorial useful, please reach out (_info@ramsocunsw.org_) if you have any issues you need help with!
