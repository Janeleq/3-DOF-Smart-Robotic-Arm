# 4-DOF-Smart-Robotic-Arm
Programming controls for TLE9879 microcontroller and arduino to execute the joints of the robotic arm<br/>
The controls are paired with MIT App Inventor using bluetooth which is then connected to the Arduino UNO.


![Robot Arm](https://user-images.githubusercontent.com/47893187/185803101-0adfc6e7-b76c-4729-9f88-58f31a729969.PNG)

# Program Flow
![Parts Control](https://user-images.githubusercontent.com/47893187/185803242-b22f92c5-1795-432e-9591-e61a918d5326.PNG)
<br/>Upon bluetooth pairing between the MIT application and arduino, buttons on the applications can be held to send a one-byte integer, declared m, to the arduino software to run specific codes.
