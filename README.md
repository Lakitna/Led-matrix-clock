# Led matrix clock
A discovery project about data design within the confinements of a 24x24 single color led matrix. I'm using the current time as the dataset.

MAX7219 IC's are driving each of the 9 8x8 matrices. This [library](https://github.com/markruys/arduino-Max72xxPanel) is driving the chips.

Since the focus of this project is the way the time is displayed, I haven't bothered adding a real time clock (RTC) module yet. But I have written the code so that it can be added easily.

<!--## Modes
1. numberClock()
2. abstractClock(1)
3. abstractClock(2)
4. barsClock()
-->