
SERIAL_PORT=${SERIAL_PORT:-/dev/ttyUSB0}
pio run --target upload --upload-port $SERIAL_PORT && \
    pio device monitor --baud 9600 --port $SERIAL_PORT
