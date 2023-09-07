import socket
import struct
from time import time
import wrapper_pb2 as wr

class FiraClient:

    def __init__(self, 
            vision_ip="224.5.23.2",
            vision_port=10015):
        """
        Init SSLClient object.
        Extended description of function.
        Parameters
        ----------
        vision_ip : str
            Multicast Vision IP in format '255.255.255.255'. 
        vision_port : int
            Vision Port up to 1024. 
        """

        self.vision_ip = vision_ip
        self.vision_port = vision_port

        self.vision_sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.vision_sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.vision_sock.setsockopt(socket.IPPROTO_IP, socket.IP_MULTICAST_TTL, 128)
        self.vision_sock.setsockopt(socket.IPPROTO_IP, socket.IP_MULTICAST_LOOP, 1)
        self.vision_sock.setsockopt(socket.IPPROTO_IP, socket.IP_ADD_MEMBERSHIP, struct.pack("=4sl", socket.inet_aton(self.vision_ip), socket.INADDR_ANY))
        self.vision_sock.bind((self.vision_ip, self.vision_port))

        # self.vision_sock.setblocking(True)
        self.frame = None
        self.det_frame = None

    def receive_frame(self):
        """Receive package and decode."""
        data = None
        while True:
            try:
                data, _ = self.vision_sock.recvfrom(1024)
            except Exception as e:
                print(e)
            if data != None:
                break

        if data != None:
            decoded_data = wr.SSL_WrapperPacket().FromString(data)
        print(decoded_data)
        # return self.frame, self.det_frame

a = FiraClient()
while(1):
    a.receive_frame()
	