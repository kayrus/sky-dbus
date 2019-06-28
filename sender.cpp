
#include <stdio.h>

#include <QtCore/QCoreApplication>
#include <QtDBus/QtDBus>

#include "callbackclass.h"

callbackClass::callbackClass(QObject *parent) : QObject(parent)
{
    if (!QDBusConnection::sessionBus().isConnected()) {
        fprintf(stderr, "Cannot connect to the D-Bus session bus.\n"
                "To start it, run:\n"
                "\teval `dbus-launch --auto-syntax`\n");
    }

    QDBusConnection::sessionBus().connect("", "/", "red.tel.sky", "recv_message", this, SLOT(recvMsg(QString,QString)));

}

void callbackClass::recvMsg(QString sender, QString text){
    qDebug() << "From " << sender << " : " << text;
}

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);

#if 1
    QDBusReply<QString> reply;
    if (!QDBusConnection::sessionBus().isConnected()) {
        fprintf(stderr, "Cannot connect to the D-Bus session bus.\n"
                "To start it, run:\n"
                "\teval `dbus-launch --auto-syntax`\n");
        return 1;
    }

    QDBusInterface iface("red.tel.sky", "/", "", QDBusConnection::sessionBus());

    if (iface.isValid()) {
        const char *option = "";
        if (argc > 1){
            option = argv[1];
        }

        if((argc == 3) && (option[0] == 's')){
            //arg[1] - s, arg[2] - status text
            reply = iface.call("statusChange", argv[2]);
        } else if ((argc == 4) && (option[0] == 'm')) {
            //arg[1] - m, arg[2] - uri (example : "sip:hieu@sky4.be"), arg[3] - msg text
            reply = iface.call("sendMessage", argv[2], argv[3]);
        } else if ((argc == 2) && (option[0] == 'l') && (option[1] == 'o')) {
            //logout command
            //arg[1] - lo
            reply = iface.call("logout");
        } else if ((argc == 7) && (option[0] == 'l') && (option[1] == 'i')) {
            //login command
            //const QString &signinAddress, const QString &domainUser, const QString &pass, const QString &ip, const int &port
            //arg[1] - li
            reply = iface.call("login", argv[2], argv[3], argv[4], argv[5],  argv[6] );
        } else if ((argc == 2) && (option[0] == 'c') && (option[1] == 'b')) {
            //callback test command
            //arg[1] - cb
            callbackClass cb;
            app.exec();
        } else if ((argc == 3) && (option[0] == 'j') && (option[1] == 'm')) {
            //callback test command
            //arg[1] - cb
            reply = iface.call("joinMeeting", argv[2] );
        } else {
            fprintf(stderr, "Wrong input args!\n");
            return 1;
        }

        if (reply.isValid()) {
            printf("Reply was: %s\n", qPrintable(reply.value()));
            return 0;
        } else {
            fprintf(stderr, "Call failed: %s\n", qPrintable(reply.error().message()));
            return 1;
        }
    }
#endif
    fprintf(stderr, "%s\n",
            qPrintable(QDBusConnection::sessionBus().lastError().message()));

    return 1;
}
