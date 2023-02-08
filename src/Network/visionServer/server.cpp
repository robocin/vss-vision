#include "server.h"

#include <QtNetwork>
#include <QtNetwork/QUdpSocket>
#include <QtNetwork/QHostAddress>
#include <QtCore/QString>


VisionServer::VisionServer(QString address, int port){

    // create a QUDP socket
    socket = new QUdpSocket();

    if(socket->isOpen())
        socket->close();

    this->_addr.setAddress(address);
    this->_port = quint16(port);
    socket->connectToHost(address,port, QIODevice::WriteOnly, QAbstractSocket::IPv4Protocol);
    //socket->bind(this->_addr, this->_port);
}

VisionServer::~VisionServer(){
    socket->close();
}

void VisionServer::send(std::vector<Entity> &entities) {
    SSL_WrapperPacket packet;

    // SSL_WrapperPacket packet;
    SSL_DetectionFrame *frame = packet.mutable_detection();
    frame->set_camera_id(0);
    frame->set_frame_number(0);
    frame->set_t_capture(0);
    frame->set_t_sent(0);

    SSL_DetectionBall *ball = frame->mutable_balls()->Add();

    ball->set_x(entities[0].position().x);
    ball->set_y(entities[0].position().y);
    ball->set_confidence(1);
    ball->set_pixel_x(entities[0].position().x * 100);
    ball->set_pixel_y(entities[0].position().y * 100);

    // geometry
    SSL_GeometryData *geometry = packet.mutable_geometry();
    SSL_GeometryFieldSize *field = geometry->mutable_field();
    field->set_field_width(1300);
    field->set_field_length(1500);
    field->set_goal_width(100);
    field->set_goal_depth(100);
    field->set_boundary_width(100);

    // serialize packet to send
    QByteArray dgram;
    std::string data;

    packet.SerializeToString(&data);

    QString qstr = QString::fromStdString(data);
    dgram = qstr.toUtf8();
    if(socket->writeDatagram(dgram, this->_addr, this->_port) > -1){
        printf("send data\n");
    }
}