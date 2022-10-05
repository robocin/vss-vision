import socket
import struct
from time import time
import wrapper_pb2 as wr
import messages_robocup_ssl_detection_pb2 as detection_t
import messages_robocup_ssl_geometry_pb2 as geo

class PROTOClient:
    def __init__(self, ip='127.0.0.1', port=20011):    
        self.com_ip = ip
        self.com_port = port
        self.com_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.com_address = (self.com_ip, self.com_port)

    def fix_x(self, x):
        return (x * 10)
    
    def fix_y(self, y):
        return (y * 10)

    # Returns a list of entities
    def unpack(self,data):
        pass

    def run(self):
        header_offset = 10
        entity_size = 8*3 + 1
        try:
            UDP_IP = '127.0.0.1'
            UDP_PORT = 54000
            sock = socket.socket(socket.AF_INET, # Internet
                socket.SOCK_DGRAM) # UDP
            sock.bind((UDP_IP, UDP_PORT))
            print("PROTOClient :: listening on port {}\n".format(UDP_PORT))
            # pkt_create_to_send = ref_placement_pb2.VSSRef_Placement()

            # robots = pkt_create_to_send.world.robots

            # for id, rbt in robots_dict.items():
                # _robot = robots.add()
            # detection = wr.SSL_WrapperPacket.detection
            # print(dir(detection))
            while True:
                msg = wr.SSL_WrapperPacket()
                frame = msg.detection
                # frame = detection.SSL_DetectionFrame()
                ball = frame.balls.add()
                robots_blue = frame.robots_blue
                robots_yellow = frame.robots_yellow

                data, addr = sock.recvfrom(1024) # buffer size is 1024 bytes
                messageType = struct.unpack_from('c',data,0)[0].decode("utf-8")
                print("message type {}".format(messageType))
                if (messageType != 'F'): continue

                timestamp = struct.unpack_from('>I',data,1)[0]
                frameId = struct.unpack_from('>i',data,5)[0]

                frame.frame_number = frameId
                frame.t_capture = timestamp
                frame.t_sent = timestamp
                frame.camera_id = 0
                entities = ord(struct.unpack_from('c',data,header_offset-1)[0])
                print("message '{}' have {} entities on frame {} time:{}".format(messageType,entities,frameId,timestamp))

                id = ord(struct.unpack_from('c',data,header_offset + entity_size*0)[0])
                x, y, ang = struct.unpack_from('ddd',data,header_offset+1 + entity_size*0)
                ball.x = self.fix_x(x)
                ball.y = self.fix_y(y)
                ball.pixel_x = ball.x * 10
                ball.pixel_y = ball.y * 10
                ball.confidence = 1
                print(entities)
                for i in range(1,entities):
                    id = ord(struct.unpack_from('c',data,header_offset + entity_size*i)[0])
                    if(id < 200):
                        x, y, ang = struct.unpack_from('ddd',data,header_offset+1 + entity_size*i)
                        _robot = robots_blue.add()
                        _robot.robot_id = id - 100
                        _robot.x = self.fix_x(x)
                        _robot.y = self.fix_y(y)
                        _robot.orientation = ang
                        _robot.confidence = 1.0
                        _robot.pixel_x = _robot.x * 10
                        _robot.pixel_y = _robot.y * 10

                    else:
                        id = ord(struct.unpack_from('c',data,header_offset + entity_size*i)[0])
                        x, y, ang = struct.unpack_from('ddd',data,header_offset+1 + entity_size*i)
                        _robot = robots_yellow.add()
                        _robot.robot_id = id - 200
                        _robot.x = self.fix_x(x)
                        _robot.y = self.fix_y(y)
                        _robot.orientation = ang
                        _robot.confidence = 1.0
                        _robot.pixel_x = _robot.x * 10
                        _robot.pixel_y = _robot.y * 10


                data = msg.SerializeToString()
                # msg.SerializeToString()
                # msg.SSL_DetectionFrame = detection
                self.com_socket.sendto(data, self.com_address)

                # print("id {} position ({},{},{})".format(id,x,y, ang))

        except KeyboardInterrupt:
            print("\nPROTOClient :: Client closed.")
        finally:
            pass

a = PROTOClient()
a.run()
# 75 e 65
def print_about():
    print("This is the PROTOClient module.\nPlease use the PROTOClient by importing this module into your code.")

if __name__ == '__main__':
    print_about()
