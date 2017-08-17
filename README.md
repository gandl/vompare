# vompare: Calculate Volt, Ampere, Resistance and Power

A simple commandline tool to calculate the missing two values from two given ones.

## Compiling


Just type make and run the executable with two arguments

```
./vompare 1V 1A
```

## Usage

```
vompare -n no units are displayed
vompare -o vawo specify order and which units are printed
vompare -p 128 gives the precision of the calculation
vompare -d 10 is the precision being displayed
```

Two arguments are needed. 

Type of input is identified by their ending:
A for Ampere,
V for Volt,
O for Resistance (Ohm) and 
W for Power (Watt)

Or you can just pipe something like a file in. The format hast to be two values in each row.

## Dependencies
 [GNU Multiple Precision Library](https://gmplib.org/)

