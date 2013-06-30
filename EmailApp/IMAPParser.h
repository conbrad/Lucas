#ifndef IMAPPARSER_H
#define IMAPPARSER_H

#include "Email.h"
#include "Folder.h"
#include <QVector>
#include <QStringList>



class IMAPParser {

public:
    IMAPParser();
    QVector<Folder> parseFolders(QString data);
    int parseSelect(QString data);
    QVector<EmailHeader> parseHeaders(QString data);
    EmailHeader parseHeader(QString data);
    QString parseBody(QString data);

};

#endif // IMAPPARSER_H
