#ifndef IMAPCLIENT_H
#define IMAPCLIENT_H

#include "IMAPConnection.h"
#include "IMAPParser.h"
#include "Folder.h"
#include "Email.h"

class IMAPClient {

public:
    IMAPClient(QString hostname, int port);
    void connectToHost(QString username, QString password);
    void disconnect();
    bool isConnected();
    QVector<Folder> getFolders();
    int selectFolder(QString folderName);
    int getNumberOfMessages(QString folderName);
    QVector<EmailHeader> getNewestEmailHeaders(QString folderName);
    QString getEmailContent(QString id);

private:
    QVector<Folder> getFolders(QString name);
    IMAPConnection m_connection;
    IMAPParser m_parser;

};

#endif // IMAPCLIENT_H
