# Simulador de estacionamento

----
## Gerar executáveis

    make

## Remover

    make clean

## Utilização do simulador

    parking-simulator(-perfect) -c <config file> & -m <maneuvers file> & -d (DEBUG)

## Extra

### Gerador de configuração inicial

     generator -n <number of objects> & -o <output file>

Exemplo:

     generator -n "$(($RANDOM%16+1))" & -o out.txt

### Gerador de dados

    data-catch <initial config file> <maneuvers> <execution times> <initial value> <step> <final value>

Exemplo:

    for ((i=1;i<=16;i++)); do ./data-catch tests/objs"$i".txt manobras.txt $times 1 1 100; done
