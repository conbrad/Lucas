#ifndef IMAPCONNECTION_H
#define IMAPCONNECTION_H

#include <QtNetwork/QSslSocket>

class IMAPConnection : public QObject {

    Q_OBJECT

public:
    IMAPConnection(QString hostname, int port);
    ~IMAPConnection();
    void connectToHost(QString username, QString password);
    void disconnect();
    void isConnected();
    void send(const QString& request);
    void read(const QString& tag, QByteArray& response);

private:
    QSslSocket  m_socket;
    QString m_hostname;
    int m_port;


};

#endif // IMAPCONNECTION_H
