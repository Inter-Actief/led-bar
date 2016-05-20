from autobahn.asyncio.websocket import WebSocketServerProtocol, \
    WebSocketServerFactory

import logging
import asyncio

logger = logging.getLogger(__name__)


class LedBarServerProtocol(WebSocketServerProtocol):
    def __init__(self, queue):
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
            mod = importlib.import_module(animation_obj.get("animation_module", default="animations"))
            # Now, instatiate the class with the kwargs
            cls = getattr(mod, animation_obj.get("animation_class")
            instance = cls(**animation_obj["animation_parameters"])
            # And push it up the queue
            self.command_queue.put_nowait(instance)
       except:
            logger.exception("An error occurred during parsing of the message on the websocket, no animation was processed")

    def onClose(self, wasClean, code, reason):
        logger.info("Websocket connection closed [%s]: %s", code, reason)


def create_ledbar_server(queue):
    factory = WebSocketServerFactory("ws://127.0.0.1:8000")
    factory.protocol = LedBarServerProtocol(queue)

    loop = asyncio.get_event_loop()
    coro = loop.create_server(factory, '0.0.0.0', 8000)

    server = loop.run_until_complete(coro)

    return loop
