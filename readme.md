## Guitar autotuner

  This are the source codes for Arduino IDE, in order to do a guitar autotuner.

## Main objectice

  The main goal of this project is to help and simplify the tuning process, especially for beginners who are not good at tuning a guitar.

## Project's assumption

  Starting from the premise that many beginners in the field of guitar experience difficulties in the process of tuning the instrument and need assistance, we developed an automatic guitar tuner based on Arduino. Thus, by using this design, the instrument will sound as it should, the strings will be evenly tensioned, avoiding the deformation of the guitar neck over time and uneven wear of the strings.

## Main components

  For this project, I chose to use a nice Arduino UNO Rev3 SMD (which handles all the command processing), a ceramic piezoelectric sensor (for vibrations), an LM393 sound sensor (for voice), an MG995 servo motor (for turning the keys ), wires to connect the components together and leds to inform the user about the status of the tuner.

- **Arduino UNO**: Arduino is a development kit that contains a microcontroller, input/output ports, power supply and other essential components. It can be connected to a computer via a USB-B, and the code written in the Arduino IDE can be uploaded to the physical board.


  <img src="https://github.com/omuletzu/Guitar-Auto-Tuner-Arduino/assets/75565975/b9467031-345f-4cb9-867c-6395d8184dec" width="300" height="300">


- **Servo MG995**: The MG995 servo motor was used in the project due to several specific features. These include the strong torque (10 kg * cm) at 6V voltage required to turn the guitar keys and the precise feedback, the motor having the ability to precisely control and position the motor shaft, important for correct tuning. At the same time, the high durability and compatibility with Arduino can be mentioned, which make this component motor suitable for its role.


  <img src="https://github.com/omuletzu/Guitar-Auto-Tuner-Arduino/assets/75565975/aefcbef9-b1c5-4024-8290-b682d3d419fe" width="200" height="200">
  <img src="https://github.com/omuletzu/Guitar-Auto-Tuner-Arduino/assets/75565975/d7ab87e6-9c23-4810-9313-a1e1b86de21a" width="200" height="100">



- **Piezoelectric ceramic**: This sensor is very important because it is responsible for detecting the vibrations generated by the strings. It is mounted on the surface of the instrument, and the material from which it is made generates a small electrical voltage proportional to the intensity of the vibration. The signal generated by it is further processed by the software. The operating voltage is 5V, and its dimensions are quite small.


  <img src="https://github.com/omuletzu/Guitar-Auto-Tuner-Arduino/assets/75565975/d7dbcd54-7240-478d-b931-7f9923c5e7c6" width="200" height="200">


- **Sound sensor LM393**: The microphone is used to listen to the user's voice, the signal being passed on to the software, and depending on which letter it says, the tuner starts or stops (at the letter "s" it starts and at "o" it stops). Its operating voltage is 5V, and the sensitivity is quite low, which causes the user to say the letters louder for better recognition.


  <img src="https://github.com/omuletzu/Guitar-Auto-Tuner-Arduino/assets/75565975/6cbf201e-a094-4cfe-aca3-cd96a1ec75bf" width="200" height="200">


- **Breadboard**: I chose to use a breadboard because it allows us to quickly and temporarily connect components without requiring soldering. It is also a good tool for the troubleshooting process in case of errors.

  
  <img src="https://github.com/omuletzu/Guitar-Auto-Tuner-Arduino/assets/75565975/026ab58c-7d8c-41bf-9e33-bf219f6ca62e" width="300" height="200">


## How it works?

  To begin with, the user has to turn on the tuner by saying the letter 's' into the microphone and can turn it off by saying the letter 'o'. After this is turned on, one must select whether standard tuning is desired (E A D G B E) or the other type available (D A D F# B D ), then one will need to select the string they want to tune and pluck it. With the help of the piezoelectric ceramic sensor, we know what the amplitude of the vibration is, and with the help of this information, the frequency of that string can be found, using the Fast Fourier Transform algorithm. Finally, depending on the frequency of that string, the servo motor will rotate the key of the guitar, requiring this process to be repeated several times for a good tuning. Thus at the end, the entire instrument will be awarded.
            
  The standard frequencies for each string are:
    - **E 82 Hz (thickest string)**
    - **At 110 Hz**
    - **D 146 Hz**
    - **G 196 Hz**
    - **B 247 Hz**
    - **E 330 Hz (thinnest string)**

  The standard frequencies for each string are:
    - **D 73 Hz (thickest string)**
    - **A 110 Hz**
    - **D 146 Hz**
    - **F# 185 Hz**
    - **G 246 Hz**
    - **D 293 Hz (thinnest string)**

  The user will be informed when the string is close to tuning, when the frequency error is at most 3 Hz (and after that the tuner will still try to reach a better frequency if the process is continued).

  <img src="https://github.com/omuletzu/Guitar-Auto-Tuner-Arduino/assets/75565975/ae1b3221-baef-4729-8fb9-0cdd9cfbce2e" width="350" height="200">
  <img src="https://github.com/omuletzu/Guitar-Auto-Tuner-Arduino/assets/75565975/a11fd2a9-4a79-40f3-96dc-d9a678d0f1fe" width="350" height="200">


  ## Usage

  Say the letter 's' into the microphone (a green LED must light up), then press the button to select the string you want to tune (there are 6 red LEDs corresponding to each string). Place the end of the actuator on the key and pinch the string. At each pinch, the motor will be operated until another green LED lights up, which means the string should be tuned, but if the user wants, he can tune even more precisely, repeating the process a few more times. Due to the fact that the servomotor can only rotate 180 degrees, every time it reaches 0 or 180 degrees, the motor resets to 90 degrees, the user being informed of this by flashing a blue LED. Finally, the letter 'o' can be said into the microphone to turn off the device.

## Software

  The software required for this language was written in the Arduino IDE editor, which uses a language very similar to C++. This one is quite consistent, being the one that deals with processing the vibrations, in order to obtain the frequency, using Fast Fourier Transform (with the help of the "ArduinoFFT" library), processing the signal from the microphone to know what letter the user said (with the help the "uSpeech" library"), the servomotor commands (with the help of the "Servo.h" library) and all the logic for LEDs that have the role of informing the user.

  <img src="https://github.com/omuletzu/Guitar-Auto-Tuner-Arduino/assets/75565975/18b1dcb9-09c3-4931-a92a-496aae8e57a2" width="50" height="200">- *This is what a signal detected by the piezoelectric sensor looks like*
  
  <img src="https://github.com/omuletzu/Guitar-Auto-Tuner-Arduino/assets/75565975/d103426a-b28e-4b5d-a0e5-1d6560ab5b3f" width="100" height="50">- *The result of the Fast Fourier Transform algorithm (frequency in Hz), which receives as input data the vibration amplitudes (that in the above example)*

  <img src="https://github.com/omuletzu/Guitar-Auto-Tuner-Arduino/assets/75565975/7d8f54ec-c030-4e29-a522-d0c4fed2c9d7" width="450" height="250">- *Project final result*
