# Muon Detector
By Max Henstell

## What's All This Then?

This is a basic Muon detector that uses three Geiger-Müller tubes, three high-voltage supplies, and a [Teensy](http://www.pjrc.com/teensy/) (Arduino-compatible) microcontroller. The Teensy provides three PWM outputs that drive the HV supplies, and watches the outputs of the tubes for the voltage spikes characteristic of an electrical avalanche signifying an ionization event.

This detector isn't meant to be scientifically accurate; rather it was intended as a neat desktop device to make you aware of the cosmic rays passing through you at all times.

## What's Missing?

Well, first of all, I was in a bit of a rush to get this done for the 2012 holidays. I accidentally routed everything on the top layer. I meant to correct this but haven't had time. I had already milled the PCB when I realized to I went ahead and soldered everything to the top, which is a pain but do-able.

As an afterthought, I added a [MAX 7221](http://playground.arduino.cc//Main/MAX72XXHardware) LED controller chip for driving a four-digit seven-segment display. That's why you'll see mention of this in the Arduino code but not in the schematic.

Sorry for the unfinished nature of the project, I was intended as a quick present and I wasn't expecting anyone to ask me for the source. Please feel free to contact me if you have any questions about making your own.

## Write-Ups

I did a few short write-ups on my blog detailing how the Muon detector works and a few of the problems I had along the way. Check em out!

* [Part One](http://mmmaaa.xxx/blog/space-1.html)
* [Part Two](http://mmmaaa.xxx/blog/space-2.html)
* [Part Three](http://mmmaaa.xxx/blog/space-3.html)

## Special Thanks

Mil Gracias go to a few people who helped me along on making this project:

* [Robert Hart](http://www.hardhack.org.au/geiger_muller_detector), for providing the original inspiration and designs for this project.
* Christoph at [Boxtec](https://shop.boxtec.ch/), for overnighting me some awesome little [SI-180G Geiger tubes](http://shop.boxtec.ch/geiger-mueller-tube-180g-p-40722.html).
* [MightyOhm](http://mightyohm.com/blog/), who sells an awesome little [Geiger Counter kit](http://mightyohm.com/blog/products/geiger-counter/)
* The talented folks on the [GeigerCounterEnthusiasts Yahoo Group](http://tech.groups.yahoo.com/group/GeigerCounterEnthusiasts/), for helping me diagnose some power supply issues.