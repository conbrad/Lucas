#include "IMAPClient.h"
#include "IMAPTag.h"
IMAPClient::IMAPClient(QString hostname, int port) : m_connection(hostname, port) {

}

void IMAPClient::connectToHost(QString username, QString password) {
    m_connection.connectToHost(username, password);
}

void IMAPClient::disconnect() {

}

bool IMAPClient::isConnected() {
    return true;
}

QVector<Folder> IMAPClient::getFolders() {
    return getFolders("");
}

QVector<Folder> IMAPClient::getFolders(QString name) {
    QString tag = IMAPTag::getNextTag();
    QString command = QString("%1 LIST  %2/%\r\n").arg(tag, name);
    m_connection.send(command);
    QByteArray response;
    m_connection.read(tag, response);
    QVector<Folder> folders = m_parser.parseFolders(QString(response));

    for (int i = 0; i < folders.size(); i++) {
        if (folders[i].hasChildren()) {
            folders[i].setChildren(getFolders(folders[i].getName()));
        }
    }
    return folders;
}

int IMAPClient::selectFolder(QString folderName) {
    QString tag = IMAPTag::getNextTag();
    QString command = QString("%1 SELECT \"%2\"\r\n").arg(tag, folderName);
    m_connection.send(command);
    QByteArray response;
    m_connection.read(tag, response);
    return m_parser.parseSelect(response);
}

int IMAPClient::getNumberOfMessages(QString folderName) {
    QString tag = IMAPTag::getNextTag();
    QString command = QString("%1 STATUS %2\r\n").arg(tag, folderName);
    m_connection.send(command);
    QByteArray response;
    m_connection.read(tag, response);
    return m_parser.parseSelect(response);
}

QVector<EmailHeader> IMAPClient::getNewestEmailHeaders(QString folderName) {
    QVector<EmailHeader> headers;
    int maxID = selectFolder(folderName);

    // No emails in the folder
    if (maxID == 0) {
        return headers;
    }

    int minID = maxID - 10;
    if (minID < 1) {
        minID = 1;
    }

    QString tag = IMAPTag::getNextTag();
    QString command = QString("%1 FETCH %2:%3 (FLAGS BODY[HEADER.FIELDS (FROM SUBJECT)])\r\n").arg(tag, QString::number(minID), QString::number(maxID));
    m_connection.send(command);
    QByteArray response;
    m_connection.read(tag, response);
    headers = m_parser.parseHeaders(response);
    return headers;
}

QString IMAPClient::getEmailContent(QString id) {
    QString tag = IMAPTag::getNextTag();
    QString command = QString("%1 FETCH %2 (FLAGS BODY[TEXT])\r\n").arg(tag, id);
    m_connection.send(command);
    QByteArray response;
    m_connection.read(tag, response);
    return m_parser.parseBody(response);
}
