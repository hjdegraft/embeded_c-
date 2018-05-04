# For simulate the capture request from configd
import zmq
import msgpack

BROKER_LINGER_TIME_MS = 10000
POLL_TIMEOUT = 250 # milliseconds

context=zmq.Context()
pull_socket="ipc:///tmp/broker_pull.ipc"
push = context.socket(zmq.PUSH)
push.setsockopt(zmq.SNDHWM, 1)
push.setsockopt(zmq.LINGER, BROKER_LINGER_TIME_MS)
push.connect(pull_socket)

poller = zmq.Poller()
poller.register(push, flags=zmq.POLLOUT)

socks = dict(poller.poll(timeout=POLL_TIMEOUT))

topic="led_service.control"
body={"command": "LED_DPU_PROVISIONING_STATE"}
body={"command": "LEDCONTROL_STATE_INIT"}
body={"command": "WIFI_BLE_DONGLE_UNPLUGGED_STATE"}
push.send_multipart((topic, msgpack.packb(body)), flags=zmq.NOBLOCK)
