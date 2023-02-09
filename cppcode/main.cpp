
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <unistd.h>

extern "C" {
    #include <pigpio.h>
}

#define IR 10
#define MTR_UP 11
#define MTR_DOWN 12
#define LED 13

bool Descending = false;
bool Running = false;


int rollcount = 2;

int main() {
    std::cout << rollcount << "\n";

    while (gpioInitialise() < 0) gpioInitialise();
    
    gpioSetMode(IR, PI_INPUT);
    gpioSetMode(MTR_UP, PI_OUTPUT);
    gpioSetMode(MTR_DOWN, PI_OUTPUT);

    gpioWrite(MTR_UP, 0);
    gpioWrite(MTR_DOWN, 0);


    // Insert int that gpioRead has to be less than
    while (true) {
        if (gpioRead(IR) == 1 && !Running && !Descending && rollcount>0) {
            gpioWrite(MTR_UP, 1);
            Running = true;
	    std::cout << "Ascending\n";
        } else if (gpioRead(IR) == 0 && Running) {
            sleep(12);
            gpioWrite(MTR_UP, 0);

            Running = false;

            // Begin Descension
            Descending = true;
	    std::cout << "Descending\n";

            // Start Descending Process
            gpioWrite(MTR_DOWN, 1);
            sleep(10);
            gpioWrite(MTR_DOWN, 0);
            Descending = false;

	    // Adjustment Check
	    while (gpioRead(IR) == 1) {
		gpioWrite(MTR_UP, 1);
		sleep(6);
		gpioWrite(MTR_UP, 0);

		gpioWrite(MTR_DOWN, 1);
		sleep(5);
		gpioWrite(MTR_DOWN, 0);
	    }

	    gpioWrite(MTR_DOWN, 1);
	    sleep(10);
	    gpioWrite(MTR_DOWN, 0);

            // Updating Roll Count
            std::ifstream RollCountFile("rollcount.txt");
            std::string count;

            std::getline(RollCountFile, count);
            RollCountFile.close();

            std::ofstream RollCountWrite("rollcount.txt");
            RollCountWrite << std::stoi(count)-1;
            RollCountWrite.close();

	    rollcount = std::stoi(count)-1;

        }
    }
}
