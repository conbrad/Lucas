#ifndef EMAIL_H
#define EMAIL_H

#include <QString>

class Email
{

public:
    Email();
};

class EmailHeader {

public:
    EmailHeader();
    EmailHeader(QString subject, QString sender, QString id);
    QString getSubject();
    QString getSender();
    QString getID();

private:
    QString m_subject;
    QString m_sender;
    QString m_id;
};

#endif // EMAIL_H
