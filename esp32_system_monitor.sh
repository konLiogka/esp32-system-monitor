#!/bin/bash

SERIAL_PORT=$(ls /dev/ttyACM* /dev/ttyUSB* 2>/dev/null | while read port; do
    if udevadm info -q property -n "$port" | grep -q 'ID_VENDOR_ID=303a'; then
        echo "$port"
        break
    fi
done)

if [ -z "$SERIAL_PORT" ]; then
    exit 1
fi


stty -F $SERIAL_PORT 115200 cs8 -cstopb -parenb -echo
sleep 2

exec 3> $SERIAL_PORT

while true; do
    TIME=$(date +%H:%M)
    CPU=$(top -bn1 | grep "Cpu(s)" | awk '{printf "%d", $2}')
    RAM=$(free | grep Mem | awk '{printf "%d", $3/$2 * 100}')
    
    DATA="$TIME,$CPU,$RAM"

    echo "$DATA" >&3

    sleep 5
done


