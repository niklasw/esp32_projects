#!/bin/bash

[ -d src -a -f platformio.ini ] || { echo "Wrong dir"; exit 1; }


SERIAL_PORT=${SERIAL_PORT:-/dev/ttyUSB0}

if [ -e "$SERIAL_PORT" ]
then
    pio run --target upload --upload-port $SERIAL_PORT && \
        pio device monitor --baud 9600 --port $SERIAL_PORT
else
    echo "Serial port $SERIAL_PORT not found. Build only."
    pio run
fi

