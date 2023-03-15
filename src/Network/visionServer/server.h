#ifndef SERVER_H
#define SERVER_H

#include <QtNetwork/qtnetworkglobal.h>
#include <QtNetwork/qudpsocket.h>
#include <QtNetwork/qhostaddress.h>
#include <QtCore/qstring.h>

#include "messages_robocup_ssl_detection.pb.h"
#include "messages_robocup_ssl_geometry.pb.h"
#include "wrapper.pb.h"
#include "command.pb.h"
#include "common.pb.h"
#include "packet.pb.h"


#ifndef EXTERNAL_COMPILATION
    #include "Entity/Entity.h"
    #include "Utils/Utils.h"
#endif

class VisionServer
{
public:
    VisionServer(QString address, int port);
    ~VisionServer();
    void send(std::vector<Entity> &entities);

    QHostAddress _addr;
    quint16 _port;

private:
    QUdpSocket *socket;
    QUdpSocket *socket_ref;


};
#endif /* SERVER_H */
