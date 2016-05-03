from asyncio import Queue
from threading import Thread

from serial_client import SerialClient
from websocket_server import *

def main():
    # The queue that holds animation directives from the websocket thread to
    # the serial communication thread
    command_queue = Queue(maxsize=1)

    # Initialise the serial client
    serial_client = SerialClient("/dev/ttyACM0", command_queue, baudrate=115200)

    # Initialise the websocket server
    ledbar_server = create_ledbar_server(command_queue)

    # Run the websocket server in a seperate thread
    ledbar_server_thread = Thread(target=ledbar_server.run_forever)

    # Run the serial client in a seperate thread
    serial_client_thread = Thread(target=serial_client.run_forever)

    ledbar_server_thread.start()
    serial_client_thread.start()

    try:
        ledbar_server_thread.join()
        serial_client_thread.join()
    except:
        ledbar_server.stop()
        serial_client.stop()

if __name__ == "__main__":
    main()
