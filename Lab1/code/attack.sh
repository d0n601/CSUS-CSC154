#!/bin/bash
SECONDS=0
value=0
while [ 1 ]
do
  value=$(( $value + 1 ))
  duration=$SECONDS
  echo "$(($duration / 60)) minutes and $(($duration %60)) seconds elapsed."
  echo "The program has been running for $value times."
  ./stack
done
