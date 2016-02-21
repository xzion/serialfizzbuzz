#include "math.h"

#define MAX_CHAR 5
#define ASCII_0 48
#define ASCII_9 57

char serial_input[MAX_CHAR];
int char_position;
bool string_ready;

void reset_input() {
    memset(serial_input, 0, sizeof(serial_input));
    char_position = 0;
    string_ready = false;
}

void setup() {
    reset_input();
    Serial.begin(9600);
    Serial.print("FizzBuzz starting...\n");
}

void loop() {
    if (string_ready) {
        int input_number = 0;
        // Convert the string to an integer
        for (int i = 0; i < char_position; i++) {
            char c = serial_input[i];
            if (c < ASCII_0 || c > ASCII_9) {
                // Character is invalid
                Serial.print("Invalid input\n");
                reset_input();
                return;
            }

            // Convert using powers of 10
            input_number += (int) (c - ASCII_0) * pow(10, char_position-1-i);
        }

        // Do the FizzBuzz
        if (input_number % 3 == 0 && input_number % 5 == 0) {
            Serial.print("FizzBuzz\n");
        } else if (input_number % 3 == 0) {
            Serial.print("Fizz\n");
        } else if (input_number % 5 == 0) {
            Serial.print("Buzz\n");
        } else {
            Serial.printf("%d\n", input_number);
        }

        // Reset
        reset_input();
    }
}

void serialEvent() {
    while (Serial.available()) {
        char new_char = (char)Serial.read();
        Serial.print(new_char);

        if (new_char == '\r' || new_char == '\n') {
            if (char_position > 0) {
                // Process the string
                string_ready = true;
                break;
            }
        } else {
            // Append and increment
            serial_input[char_position++] = new_char;
            if (char_position >= MAX_CHAR) {
                // Reached the maximum limit, print a newline and process
                Serial.print('\n');
                string_ready = true;
                break;
            }
        }
    }
}