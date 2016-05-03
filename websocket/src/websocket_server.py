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
        pass

    def onClose(self, wasClean, code, reason):
        logger.info("Websocket connection closed [%s]: %s", code, reason)


def create_ledbar_server(queue):
    factory = WebSocketServerFactory("ws://127.0.0.1:8000")
    factory.protocol = LedBarServerProtocol(queue)

    loop = asyncio.get_event_loop()
    coro = loop.create_server(factory, '0.0.0.0', 8000)

    server = loop.run_until_complete(coro)

    return loop
