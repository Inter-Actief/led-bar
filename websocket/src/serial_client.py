import threading
from serial import serial_for_url

class SerialClient(threading.Thread):
    def __init__(self, uri, queue, baudrate=9600):
        super(SerialClient, self).__init__()

        self.uri = uri
        self.command_queue = queue
        self.connection = None

        self.current_animation = None

    def connect(self):
        self.connection = serial_for_url(self.uri)
        self.connection.baudrate = self.baudrate

    def run(self):
        print("running forever!")
        while True:
            if not (self.command_queue.empty() and self.current_animation):
                self.current_animation = yield self.command_queue
                self.current_animation.pre_animation()

            keyframe = self.current_animation.animate()

            # First read a byte, then start sending
            serial.read(size=1)

            # Then start writing elements back
            for pixel in keyframe:
                serial.write(pixel.r)
                serial.write(pixel.g)
                serial.write(pixel.b)

            serial.flush()

    def stop(self):
        pass
