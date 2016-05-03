from serial import serial_for_url

class SerialClient(object):
    def __init__(self, uri, queue, baudrate=9600):
        self.uri = uri
        self.command_queue = queue
        self.connection = None

    def connect(self):
        self.connection = serial_for_url(self.uri)
        self.connection.baudrate = self.baudrate

    def run_forever(self):
        pass

    def stop(self):
        pass
