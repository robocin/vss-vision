#include "server.h"

#include <QtNetwork>
#include <QtNetwork/QUdpSocket>
#include <QtNetwork/QHostAddress>
#include <QtCore/QString>


VisionServer::VisionServer(QString address, int port){

    // create socket
    this->socket = new QUdpSocket();
    
    if (this->socket->isOpen())
        this->socket->close();
    
    this->socket->setSocketOption(QAbstractSocket::MulticastTtlOption, 1);
    this->_addr.setAddress(address);
    this->_port = quint16(port);
}

VisionServer::~VisionServer(){
    socket->close();
}

void VisionServer::send(std::vector<Entity> &entities) {
    SSL_WrapperPacket packet;

    SSL_DetectionFrame *frame = packet.mutable_detection();
    frame->set_camera_id(0);
    frame->set_frame_number(0);
    frame->set_t_capture(0);
    frame->set_t_sent(0);

    for(int i=0;i<entities.size();i++){
        if(i == 0){
            SSL_DetectionBall *ball = frame->mutable_balls()->Add();
            ball->set_x(entities[0].position().x * 10);
            ball->set_y(entities[0].position().y * 10);
            ball->set_confidence(1);
            ball->set_pixel_x(entities[0].position().x * 100);
            ball->set_pixel_y(entities[0].position().y * 100);
        } else{
            if((int)entities[i].team() == Color::YELLOW){
                SSL_DetectionRobot *robot = frame->mutable_robots_yellow()->Add();
                robot->set_robot_id(entities[i].id());
                robot->set_x(entities[i].position().x * 10);
                robot->set_y(entities[i].position().y * 10);
                robot->set_orientation(entities[i].angle());
                robot->set_confidence(1);
                robot->set_pixel_x(robot->x()*100);
                robot->set_pixel_y(robot->y()*100);
            }else if((int)entities[i].team() == Color::BLUE){
                SSL_DetectionRobot *robot = frame->mutable_robots_blue()->Add();
                robot->set_robot_id(entities[i].id());
                robot->set_x(entities[i].position().x * 10);
                robot->set_y(entities[i].position().y * 10);
                robot->set_orientation(entities[i].angle());
                robot->set_confidence(1);
                robot->set_pixel_x(robot->x()*100);
                robot->set_pixel_y(robot->y()*100);
            }
        }
    }

    // geometry
    SSL_GeometryData *geometry = packet.mutable_geometry();
    SSL_GeometryFieldSize *field = geometry->mutable_field();
    field->set_field_width(1300);
    field->set_field_length(1500);
    field->set_goal_width(400);
    field->set_goal_depth(100);
    field->set_boundary_width(100);
    field->set_penalty_area_depth(150);
    field->set_penalty_area_width(700);

    // serialize packet to send
    QByteArray datagram(static_cast<int>(packet.ByteSizeLong()), static_cast<char>(0));
    packet.SerializeToArray(datagram.data(), datagram.size());

    // send packet
    socket->writeDatagram(datagram,this->_addr, this->_port);
}