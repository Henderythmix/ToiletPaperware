# Toiletpaperware
~~Or something similar idk what to call it lol~~

This is the software end of the Toilet Paper Refiller.

The purpose of this code is to determine what tasks to perform if an action is requested, such as...
- Swapping Toilet Paper Rolls
- Indicating that toilet paper is low
- etc.

## Components
The project uses python on a raspberry pi to communicate with the hardware pins.

to make sure you have all the packages required, run:
`sudo apt install gcc pigpio nodejs`

once downloaded, you just have to run
```
npm install
make build
make run
```

## Planning
This information is not relevant to the code, but it allows us to determine how we can write the code

### Notes

Toilet Paper:
- Diameter: 12.5cm
- Radius: 6.25cm
- Width: 10cm

