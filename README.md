# HealthCareAVR-IoTCellularAssistant

### What problem are you going to solve?

In today's age, the merging of technology and healthcare has sparked pioneering solutions that transform the landscape of medical treatment. The intelligent personal healthcare system utilizing AVR-IoT Cellular Mini epitomizes an advanced fusion of information technology and personalized healthcare. This state-of-the-art system leverages the capabilities of the AVR-IoT Cellular Mini, an embedded development platform that seamlessly integrates microcontroller functionalities with cellular connectivity. Through the integration of sophisticated sensors and cutting-edge artificial intelligence algorithms, this solution establishes an unparalleled ecosystem for personalized healthcare and continuous monitoring.

![Texto alternativo](static/Fig_1.jpeg)


**Some of the problems to be solved by An Intelligent Personal Healthcare System leveraging AVR-IoT Cellular Mini are as follows:**

1. **Remote Patient Monitoring:** The system can track vital signs, such as heart rate, blood pressure, and temperature, enabling remote monitoring of patients. This can be particularly useful for individuals with chronic conditions or elderly patients who require continuous supervision.

2. **Timely Alerts and Notifications:** By integrating sensors and AI algorithms, the system can detect anomalies in health metrics and send alerts to healthcare providers or family members in real-time, facilitating timely intervention in case of emergencies or sudden health issues.

3. **Improved Accessibility to Healthcare:** Especially in remote or underserved areas, this system can bridge the gap by providing access to basic healthcare services. Patients can receive consultations, check-ups, or guidance without physically visiting healthcare facilities.

4. **Data-Driven Insights:** The collected data can be analyzed to generate insights into individual health trends, allowing for personalized recommendations and predictive analysis to prevent potential health issues.

### What are you going to build to solve this problem?

The issue at hand is the insufficient information available to doctors when patients visit their clinics. This inadequacy primarily arises from the loss of essential data required for accurate diagnoses over time. Critical information like blood pressure, heart signals, heart sounds, blood sugar levels, and others often go missing. This data is pivotal for prompt disease detection and making informed diagnoses.

To address this challenge, we propose leveraging the AVR-IoT Cellular Mini system. This system is designed to gather such crucial health data and transmit it to a server. Once received, the server employs deep-learning models to analyze the data, assessing any potential risks or health concerns for the user. This innovative approach ensures the preservation and analysis of vital health data, enabling timely risk detection and enhanced diagnostic accuracy.

Upon completion of the pre-analysis, the server sends a notification to the user. This notification can be exhibited on an LCD screen or relayed to the M5ATOM Echo Smart Speaker. The M5 will act as a voice playback system, enabling it to convey messages affirming that everything is satisfactory or advising the user to contact their doctor as necessary.

![Texto alternativo](static/CaseAssistant.png)

### Hardware:
1. AVR-IoT Mini Cellular
2. Cardio chip: BMD101
3. SPO2 sensor: MAX30102
4. MLX90640 IR Array Thermal Imaging Camera, 32×24 Pixels, 55° Field of View,  I2C Interface
5. M5Stack S3
6. Raspberry Pi as a server

### Software:
1. Embedded software for Cardio chip (if required)
2. Embedded software for SPO2 sensor (if required)
3. Software for Mini MLX90640
4. Server-side software for Raspberry Pi
5. Deep-learning models for health data analysis
6. Software for user interface and notifications
7. Communication protocols 
8. Development tools and libraries for software development and integration



### Assistant:

The assistant is composed of a series of hardware components, which when combined, enable the capture, communication, and analysis of ECG signals.

![Texto alternativo](static/RobotFace.png)



The first of these hardware components and the heart of this assistant is the AVR-IoT Mini Cellular. This development system, created by Microchip Technology (EV70N78A), is a comprehensive platform that can be used to evaluate and develop IoT solutions. It incorporates the following components:

- AVR128DB48 AVR® microcontroller
- ATECC608B CryptoAuthentication™ device
- 25CSM04 serial EEPROM 4Mb
- GM02S cellular module
- 824-2170MHz cellular flexible antenna
- Prepaid SIM card from Truphone 150MB data included
- Nano SIM card holder
- eSIM footprint
- 5 user LEDs
- 2 mechanical buttons
- VMK3-9002 32.768kHz crystal
- VEML3328 color sensor
- MCP9808 temperature sensor
- Adafruit feather-compatible edge connector
- Qwiic® I2C connector
- Onboard debugger
- Board identification in Microchip Studio and Microchip MPLAB® X
- One green power and status LED
- Virtual serial port (USB CDC)
- Two logic analyzer channels (debug GPIO)

![Texto alternativo](static/Microchip_EV70N78A_BL.png.jpeg)

Additionally, the development board is compatible with the cellular Arduino library and offers USB, battery, and external-input power options. It includes an MCP73830 Li-ion/LiPo battery charger with charge status LED and two fixed power domains: 1.8V and 3.3V.

