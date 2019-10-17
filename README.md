# Week 2 Labs 
Msc Creative Computing
Physical Computing #2 1 w/ Phoenix Perry
By Stuart Leitch

## Lab 00 - Leds in Serial and Parallel

I approached both of these questions from both mathematical (on paper) and physical (with metal) perspectives.

### How many leds can you hook up with a 220k resistor in serial before running out of voltage?

Assuming this is a typo that is supposed to refer to using 220 Ohm resistors, not 220k.

We don't have specific specifications for the LEDs, but through some searching, red LEDs have the lowest voltage requirements of common LEDs, at about 1.8V forward voltage [Wikipedia](https://en.wikipedia.org/wiki/LED_circuit), compared to around 3V for a blue LED. An LED will light up more dimly at a lower voltage, but it will eventually get spread too thin. 

Considering that in serial, to get them to light up, the voltage from the Arduino of 5v must exceed the summed voltage required for all the LEDs.

Where n is the number of LEDs:
5v = 1.8v * n 

We can divide to get n:
5/1.8 = 2.78 (rounded to the hundredths)

This is very close to 3, so we would likely get 3 dim red LEDs to light up. To verify this in the real world, we plug in 3 LEDs and see.

Sure enough, the 3 red LEDs are very dimly lit. 

![3 red LEDs](https://github.com/Toruitas/pcomp-wk2/blob/master/3redleds.JPG)

Adding another (not pictured) resulted in all the LEDs remaining dark.


### How many leds can you hook up with a 220k resistor in parallel before running out of voltage?

In parallel, the Voltage applied is the same for each branch of the circuit. Voltage in is 5v and voltage out is ~3.2v for each branch. The LEDs aren't at risk of having too little voltage. However, an Arduino has an upper limit on how much Amperage it can supply across the board - 500mA. So the limiting factor for how many LEDs can be lit isn't actually voltage, but Amperage.

Since in parallel, total current is simply the sum of the current of each branch circuit, we can make a very easy calculation for the total current of the board.

It = I1 + I2 + I3 + ... + In
Or: It = sum(I1, In)

And the similarly calculated resistance:

1/Rt = 1/R1 + 1/R2 + 1/R3 + ... + 1/Rn
Or: Rt = sum(R1, Rn)

While voltage is the same for each branch.

V = V1 = V2 = V3 = ... = Vn

We know that we are using a 220 resistor on each branch, but we don't know the resistance of an LED itself. We take a shortcut here and just measure the current through the circuit at the LED, which comes to about 13.7mA on the voltage detector for a single branch. Versus ~22.7mA with a circuit of only the resistor. So clearly, the LED adds resistance to the circuit of about 9mA.

Each branch consisting of a red LED and 220 resistor will have a current of 13.7mA, so plugging that into our equation, we can again find N. If we use different resistors or different LEDs, the math gets more complicated.

0.5 = n * 0.0137
n = 36.49 LEDs

So given that we cannot have half an LED, the Arduino will max out at 36 LEDs.

I did start building these circuits, but after 13 very bright LEDs I realized that I couldn't even fit enough LEDs on the rbead board to get to 36. It would max out at 30.

![13 red LEDs](https://github.com/Toruitas/pcomp-wk2/blob/master/13redleds.JPG)

## Lab 01 - Lab 01 - Serial Data

This excites me. Finally, a console! With input!

To test how the serial port's console works with the Arduino, I wrote a short text RPG-style interaction based on 2001: A Space Odyssey. Try to convince HAL to open the airlock door.

However there's still a mystery around how to get the Arduino to wait for user input on the Serial port. Originally I thought I could use an if with !value but that trick doesn't work so well with strings in C++ evidently, it just resolves to true. So I needed to add string validation to make sure the string is longer than 0 characters.

This here helped a bit with creating a basic string validation.: https://www.arduino.cc/en/Tutorial/StringLength

Which allowed the game to become somewhat playable. 

I'm leaving as it is. There are issues around:
1) Repeating text
2) Input re-assignment

## Lab 02 - Potentiometers (Knobs)

The potentiometer, AKA pot, is something I'm still wrapping my head around.

Voltage comes in through the left side, and gets split according to the pot into the middle and right sides. The more "open" the pot is, the more voltage goes through the middle. 

How does it do that? 

There are different amounts of resistance on the middle and right sides, and turning the pot adjusts them. When the middle has higher resistance (pot closed) than the right, voltage goes through the right side to ground. When the middle has lower resistance than the right, voltage goes through the middle to the LED (or to a data pin).

Click to view video.
[![POT VIDEO](https://i9.ytimg.com/vi/ntq5NYOJ80w/mqdefault.jpg?time=1571225821394&sqp=COSAnO0F&rs=AOn4CLCm6OO1u3y4EQ2oLSHon08NQmXibA)](https://youtu.be/ntq5NYOJ80w "POT VIDEO")

## Lab 03 - Light Dependent Resistors

LDRs are resistors who start with low resistance which goes down depending on the amount of light supplied to it.

On this circuit with a single LED, with the LDR uncovered and in the bstartling rightness of the London afternoon, the LDR has low resistance and the LED is lit up. 

Once I cover the LDR with my hand, the LED dims as the resistance goes up so high that the LED doesn't get enough juice.

Click to view video.
[![LDR VIDEO](https://i9.ytimg.com/vi/sQP9ijFro-E/mqdefault.jpg?time=1571226578300&sqp=CLyFnO0F&rs=AOn4CLAV-wMnqJomGorDPHz9EFnrynsDHw)](https://youtu.be/sQP9ijFro-E "LDR VIDEO")

## Lab 04 - Playing with Common Sensors

My group was given a baggie which included a ![Square Force Sensitive Resistor](https://learn.sparkfun.com/tutorials/force-sensitive-resistor-hookup-guide/all). 

The given schematic was relatively straightforward, with the only truly tricky part being the lack of a 3.3k Ohm resistor in the supplies. To create such a resistor, we put 3x 10k Ohm resistors in parallel which dropped the resistance to 3.3k Ohms according to the formula: 

1/Rt = 1/10k + 1/10k + 1/10k
-> Rt = 10k/3 = 3.3k Ohms

![Schematic](https://cdn.sparkfun.com/r/600-600/assets/learn_tutorials/5/1/0/fritzing_example_bb_2.png)

After uploading the given Arduino sketch to the hardware and connecting it to my machine, we tested the setup.

By pinching the FSR at varying levels, we determined that a light pinch leads to high resistance, while a heavy pinch led to low resistance. 

Why is it that way? Take for example, a mouseclick. A click opens a circuit, telling the computer that the gesture of a "click" happened. Then when the pressure on the mouse button relaxes and ends, the resistance rises again, closing that part of the circuit and going back to the base state.

It's also important to note that this takes advantage of the Analog input pin.

Click to view video.
[![FSR VIDEO](https://github.com/Toruitas/pcomp-wk2/blob/master/fsr.JPG)](https://youtu.be/jNmjA7At94k "FSR VIDEO")