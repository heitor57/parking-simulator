# Parking simulator

## Generate executables

    make

## Clean

    make clean

## How to use the simulator 

    parking-simulator(-perfect) -c <config file> & -m <maneuvers file> & -d (DEBUG)

## Extra

### Initial setup generator

     generator -n <number of objects> & -o <output file>

Example:

     generator -n "$(($RANDOM%16+1))" & -o out.txt

### Data generator

    data-catch <initial config file> <maneuvers> <execution times> <initial value> <step> <final value>

Example:

    for ((i=1;i<=16;i++)); do ./data-catch tests/objs"$i".txt manobras.txt $times 1 1 100; done
