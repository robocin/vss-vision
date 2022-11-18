import socket
import struct
from time import time
import wrapper_pb2 as wr
import messages_robocup_ssl_detection_pb2 as detection_t
import messages_robocup_ssl_geometry_pb2 as geo
import random
import numpy as np
import time

class PROTOClient:
    def __init__(self, ip='224.5.23.2', port=10006):    
        self.com_ip = ip
        self.com_port = port
        self.com_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.com_address = (self.com_ip, self.com_port)

    def fix_x(self, x):
        return float((x * 10) - 750)

    def fix_y(self, y):
        return float((y * 10) - 600)

    def normalizeAngle(self, a):
        if (a>180): return -360+a
        if (a<-180): return 360+a
        return a

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
                ball = frame.balls.add()
                robots_blue = frame.robots_blue
                robots_yellow = frame.robots_yellow
                geo = msg.geometry
                field = geo.field

                field.field_length = 1500
                field.field_width = 1300
                field.goal_width = 400
                field.goal_depth = 100
                field.boundary_width = 0
                field.penalty_area_depth = 150
                field.penalty_area_width = 700
                # field.ball_radius = 50
                # field.max_robot_radius = 300

                cam = geo.calib.add()
                cam.camera_id = 0
                cam.focal_length = 0.2
                cam.distortion = 0.2
                cam.principal_point_x = 300
                cam.principal_point_y = 300
                cam.q0 = 0.7
                cam.q1 = 0.7
                cam.q2 = 0.7
                cam.q3 = 0.7
                cam.tx = 0
                cam.ty = 0
                cam.tz = 3500
                cam.derived_camera_world_tx = 0
                cam.derived_camera_world_ty = 0
                cam.derived_camera_world_tz = 3500

                data, addr = sock.recvfrom(1024) # buffer size is 1024 bytes
                messageType = struct.unpack_from('c',data,0)[0].decode("utf-8")
                print("message type {}".format(messageType))
                if (messageType != 'F'): continue

                timestamp = struct.unpack_from('>I',data,1)[0]
                frameId = struct.unpack_from('>i',data,5)[0]

                frame.frame_number = frameId
                frame.t_capture = time.time()
                frame.t_sent = time.time()
                frame.camera_id = 0
                entities = ord(struct.unpack_from('c',data,header_offset-1)[0])
                print("message '{}' have {} entities on frame {} time:{}".format(messageType,entities,frameId,timestamp))

                id = ord(struct.unpack_from('c',data,header_offset + entity_size*0)[0])
                x, y, ang = struct.unpack_from('ddd',data,header_offset+1 + entity_size*0)
                ball.x = self.fix_x(x)
                ball.y = self.fix_y(y)
                # ball.z = 0
                # ball.area = 2
                ball.pixel_x = ball.x  / 10
                ball.pixel_y = ball.y / 10
                ball.confidence = 1

                for i in range(1,entities):
                    id = ord(struct.unpack_from('c',data,header_offset + entity_size*i)[0])
                    if(id < 200):
                        x, y, ang = struct.unpack_from('ddd',data,header_offset+1 + entity_size*i)
                        _robot = robots_blue.add()
                        _robot.robot_id = id - 100
                        _robot.x = self.fix_x(x)
                        _robot.y = self.fix_y(y)
                        _robot.orientation = ang
                        _robot.confidence = 1
                        _robot.pixel_x = _robot.x * 100
                        _robot.pixel_y = _robot.y * 100

                    else:
                        id = ord(struct.unpack_from('c',data,header_offset + entity_size*i)[0])
                        x, y, ang = struct.unpack_from('ddd',data,header_offset+1 + entity_size*i)
                        _robot = robots_yellow.add()
                        _robot.robot_id = id - 200
                        _robot.x = self.fix_x(x)
                        _robot.y = self.fix_y(y)
                        _robot.orientation = ang
                        _robot.confidence = 1
                        _robot.pixel_x = _robot.x * 100
                        _robot.pixel_y = _robot.y * 100


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
