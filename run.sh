#!/bin/bash

sizes=( 1000 2000 4000 ) 
threads=( 2 4 )
file="out.csv"

echo "size,threads,paralelo,sequencial" > $file

# tamanho das matrizes
for i in "${sizes[@]}"
do
    # número de fluxos
    for j in "${threads[@]}"
    do
        # executa 10 vezes
        for (( k=0; k<10; k++ ));
        do
            printf "size=%d threads=%d k=%d\n" $i $j $k
            ./main $i $i $i $j >> $file
        done
    done
done
