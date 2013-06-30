#include "IMAPConnection.h"
#include "IMAPTag.h"
#include <QThread>

IMAPConnection::IMAPConnection(QString hostname, int port) {
    m_hostname = hostname;
    m_port = port;
}

IMAPConnection::~IMAPConnection() {
}


void IMAPConnection::connectToHost(QString username, QString password) {
    m_socket.connectToHostEncrypted(m_hostname, m_port);
    m_socket.waitForConnected();
    QString tag = IMAPTag::getNextTag();
    QString loginCommand = QString("%1 LOGIN %2 %3\r\n").arg(tag, username, password);

    send(loginCommand);
    QByteArray responseData;
    read(tag, responseData);
}

void IMAPConnection::disconnect() {

}

void IMAPConnection::isConnected() {

}

void IMAPConnection::send(const QString& request) {
    QByteArray data;
    qDebug() << request;
    data.append(request);
    m_socket.write(data);
}

void IMAPConnection::read(const QString& tag, QByteArray& response) {
    bool doneReading = false;
    QString terminal = QString("%1").arg(tag);
    while (!doneReading) {
        m_socket.waitForReadyRead(50);
        QString data(m_socket.readAll());
        if (data.contains(terminal)) {
            doneReading = true;
        }
        response.append(data);
        qDebug() << response;
    }
}

