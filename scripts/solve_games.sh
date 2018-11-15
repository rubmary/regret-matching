#!/bin/bash

gameList='RPS alpha_beta ejemplo-1 ejemplo-2 matching_pennies'
for name in $gameList; do
	echo 'Resolviendo el juego: ' $name
	./solve_normal_form.sh $name
	echo ' '
done