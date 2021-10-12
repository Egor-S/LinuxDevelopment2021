#!/bin/dash
delay=${1:-0.1}
y=0
max_x=0
max_y=0

tput clear

tr ' ' '\01' |
while read -r line; do
	echo -n "$line" | hexdump -ve '1/1 "%_ad %_c\n"' |
	while read -r x char; do
		if [ $char != "001" ]; then
			echo "$y $x $char"
		fi
	done
	y=$(( y=y+1 ))
done | shuf |
while read -r y x char; do
	tput cup $y $x
	echo -n $char
	sleep $delay
	max_x=$(( x > max_x ? x : max_x ))
	max_y=$(( y > max_y ? y : max_y ))
	tput cup $max_y $max_x
done
echo
