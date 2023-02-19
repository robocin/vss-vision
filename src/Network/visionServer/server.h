#ifndef C5873298_24F8_46ED_B84A_3ED979543C50
#define C5873298_24F8_46ED_B84A_3ED979543C50

#include <QtNetwork/qtnetworkglobal.h>
#include <QtNetwork/qudpsocket.h>
#include <QtNetwork/qhostaddress.h>
#include <QtCore/qstring.h>

#include "Network/protobuf/proto/messages_robocup_ssl_detection.pb.h"
#include "Network/protobuf/proto/messages_robocup_ssl_geometry.pb.h"
#include "Network/protobuf/proto/wrapper.pb.h"

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

};
#endif /* C5873298_24F8_46ED_B84A_3ED979543C50 */
