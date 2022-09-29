import socket
import struct
from time import time
import wrapper_pb2 as wr
import messages_robocup_ssl_detection_pb2 as detection
import messages_robocup_ssl_geometry_pb2 as geo

class FiraClient:

    def __init__(self, 
            vision_ip='127.0.0.1',
            vision_port=20011, 
            cmd_ip='127.0.0.1',
            cmd_port=20011):
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
        self.com_ip = cmd_ip
        self.com_port = cmd_port

        self.vision_sock = socket.socket(
            socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
        self.vision_sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.vision_sock.setsockopt(socket.IPPROTO_IP, 
                        socket.IP_MULTICAST_TTL, 128)
        self.vision_sock.setsockopt(socket.IPPROTO_IP, 
                        socket.IP_MULTICAST_LOOP, 1)
        self.vision_sock.bind((self.vision_ip, self.vision_port))
        
        self.vision_sock.setblocking(True)
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
        print(data)
        # return self.frame, self.det_frame

a = FiraClient()
while(1):
    a.receive_frame()