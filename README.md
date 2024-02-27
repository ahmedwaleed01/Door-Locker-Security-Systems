# Door Locker Security System

This project is an implementation of a door locking system using two ATmega32 microcontrollers operating at a frequency of 8MHz. The system is designed based on a layered architecture model, where one microcontroller serves as the HMI_ECU (Human Machine Interface) with a 2x16 LCD and a 4x4 keypad, while the other functions as the Control_ECU with EEPROM, Buzzer, and DC Motor.

# System Workflow

## Create a System Password:

-The LCD displays "Please Enter Password."
-The user inputs a password consisting of 5 numbers, with -the LCD displaying '\*' for each number.
-The user confirms the password by re-entering it.
-HMI_ECU sends the two passwords to Control_ECU via UART.

If the passwords match, the system saves the password in the EEPROM and proceeds to the next step. If not, the process is repeated.

## Main Options:

- The LCD displays the main system options.

1- Open Door:

- The system requests the user to enter the password.
- HMI_ECU sends the entered password to Control_ECU.
- If the passwords match, the system performs the following actions:
  1- Rotates the motor for 15 seconds in the clockwise direction (CW) and displays "Door is Unlocking" on the LCD.
  2- Holds the motor for 3 seconds.
  3- Rotates the motor for 15 seconds in the anti-clockwise direction (A-CW) and displays "Door is Locking" on the LCD.

2- Change Password:

- The system requests the user to enter the current password.
- HMI_ECU sends the entered password to Control_ECU.
- If the passwords match, the system repeats the password creation process.

# Handling Incorrect Passwords:

- If the entered password does not match the stored password during the "Open Door" or "Change Password" steps, the system asks for the password once more.
- If the entered password matches, the door is opened or the password is changed (depending on the step).
- If the password does not match for the third consecutive time, the system:
- Activates the buzzer for 1 minute.
- Displays an error message on the LCD for 1 minute.
- Locks the system, preventing any input from the keypad during this time.
- Returns to the main options (Step 2) after the lockout period.
- This system provides a comprehensive security solution with user-friendly interaction via the HMI_ECU and robust control mechanisms in the Control_ECU, ensuring effective door locking and unlocking functionalities.
