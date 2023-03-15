#include "server.h"

#include <QtNetwork>
#include <QtNetwork/QUdpSocket>
#include <QtNetwork/QHostAddress>
#include <QtCore/QString>


VisionServer::VisionServer(QString address, int port){

    // create socket
    this->socket = new QUdpSocket();
    this->socket_ref = new QUdpSocket();

    if (this->socket->isOpen())
        this->socket->close();

    if (this->socket_ref->isOpen())
        this->socket_ref->close();

    this->socket->setSocketOption(QAbstractSocket::MulticastTtlOption, 1);
    this->socket_ref->setSocketOption(QAbstractSocket::MulticastTtlOption, 1);

    this->_addr.setAddress(address);
    this->_port = quint16(port);
}

VisionServer::~VisionServer(){
    socket->close();
    socket_ref->close();
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
                robot->set_robot_id(entities[i].id()-200);
                robot->set_x(entities[i].position().x * 10);
                robot->set_y(entities[i].position().y * 10);
                robot->set_orientation(entities[i].angle());
                robot->set_confidence(1);
                robot->set_pixel_x(robot->x()*100);
                robot->set_pixel_y(robot->y()*100);
            }else if((int)entities[i].team() == Color::BLUE){
                SSL_DetectionRobot *robot = frame->mutable_robots_blue()->Add();
                robot->set_robot_id(entities[i].id()-100);
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

    fira_message::sim_to_ref::Environment packet2;

    fira_message::Ball *ball = packet2.mutable_frame()->mutable_ball();

    // fira_message::Robot* robot = packet2.mutable_frame()->add_robots_blue();

    for(int i=0;i<entities.size();i++){
        if(i == 0){
            ball->set_x(entities[0].position().x);
            ball->set_y(entities[0].position().y);
            ball->set_vx(0);
            ball->set_vy(0);
            ball->set_z(0);
            ball->set_vz(0);
        } else{
            if((int)entities[i].team() == Color::YELLOW){
                fira_message::Robot* robot = packet2.mutable_frame()->add_robots_yellow();
                robot->set_robot_id(entities[i].id()-200);
                robot->set_x(entities[i].position().x);
                robot->set_y(entities[i].position().y);
                robot->set_orientation(entities[i].angle());
                robot->set_vx(0);
                robot->set_vy(0);
                robot->set_vorientation(0);
            }else if((int)entities[i].team() == Color::BLUE){
                fira_message::Robot* robot = packet2.mutable_frame()->add_robots_blue();

                robot->set_robot_id(entities[i].id()-100);
                robot->set_x(entities[i].position().x);
                robot->set_y(entities[i].position().y);
                robot->set_orientation(entities[i].angle());
                robot->set_vx(0);
                robot->set_vy(0);
                robot->set_vorientation(0);
            }
        }
    }

    fira_message::Field *field2 = packet2.mutable_field();
    field2->set_width(1.3);
    field2->set_length(1.5);
    field2->set_goal_width(0.4);
    field2->set_goal_depth(0.1);
    // field2->set_center_radius(0.1);
    // field2->set_penalty_width(0.1);
    // field2->set_penalty_depth(0.4);
    // field2->set_penalty_point(0.2);

    packet2.set_step(0);
    packet2.set_goals_blue(0);
    packet2.set_goals_yellow(0);

    QByteArray dgram2;

    dgram2.resize(packet2.ByteSize());
    packet.SerializeToArray(dgram2.data(), dgram2.size());
    QHostAddress address;
    address.setAddress("224.0.0.1");
    std::cout << dgram2.size() << std::endl;
    if(socket_ref->writeDatagram(dgram2, address, quint16(10002)) > -1){
        // printf("send data\n");
    }

}