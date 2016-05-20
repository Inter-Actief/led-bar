from autobahn.asyncio.websocket import WebSocketServerProtocol, \
    WebSocketServerFactory

import logging
import asyncio

logger = logging.getLogger(__name__)


class LedBarServerProtocol(WebSocketServerProtocol):
    def __init__(self, queue):
        super(LedBarServerProtocol, self).__init__()
        self.command_queue = queue

    def onConnect(self, request):
        logger.info("Client connected: %s", request.peer)

    def onOpen(self, request):
        logger.info("WebSocket started listening!")

    def onMessage(self, payload, isBinary):
        try:
            # We would expect the payload to be binary
            animation_obj = json.loads(payload.decode('utf-8'))
            # We then try to import the specified module
            mod = importlib.import_module("animations")
            # Now, instatiate the class with the kwargs
            cls_name = animation_obj.get("animation_class")

            if not re.match(r'^[a-zA-Z_][a-zA-Z0-9_]*$', cls_name):
                return

            cls = getattr(mod, cls_name)
            instance = cls(**animation_obj["animation_parameters"])
            # And push it up the queue
            self.command_queue.put_nowait(instance)
        except:
            logger.exception("An error occurred during parsing of the message on the websocket, no animation was processed")

    def onClose(self, wasClean, code, reason):
        logger.info("Websocket connection closed [%s]: %s", code, reason)


def create_ledbar_server(queue):
    factory = WebSocketServerFactory("ws://127.0.0.1:9000")
    factory.protocol = LedBarServerProtocol(queue)

    loop = asyncio.get_event_loop()
    coro = loop.create_server(factory, '0.0.0.0', 9000)

    server = loop.run_until_complete(coro)

    print("hai")

    return loop
