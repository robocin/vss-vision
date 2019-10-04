import socket
import struct

class VSSClient:
    def __init__(self):
        pass

    # Returns a list of entities
    def unpack(self,data):
        pass

    def run(self):
        header_offset = 5
        entity_size = 8*3 + 1
        try:
            UDP_IP = '127.0.0.1'
            UDP_PORT = 54000
            sock = socket.socket(socket.AF_INET, # Internet
                socket.SOCK_DGRAM) # UDP
            sock.bind((UDP_IP, UDP_PORT))
            print("VSSClient :: listening on port {}\n".format(UDP_PORT))
            while True:
                data, addr = sock.recvfrom(1024) # buffer size is 1024 bytes
                frameId = struct.unpack_from('>i',data,0)[0]
                entities = ord(struct.unpack_from('c',data,4)[0])
                print("message have {} entities on frame {}".format(entities,frameId))
                for i in range(0,entities):
                    id = ord(struct.unpack_from('c',data,header_offset + entity_size*i)[0])
                    # print("id {} ".format(id))
                    x, y, ang = struct.unpack_from('ddd',data,header_offset+1 + entity_size*i)
                    print("id {} position ({},{},{})".format(id,x,y, ang))

        except KeyboardInterrupt:
            print("\nVSSClient :: Client closed.")
        finally:
            pass


def print_about():
    print("This is the VSSClient module.\nPlease use the VSSClient by importing this module into your code.")

if __name__ == '__main__':
    print_about()
