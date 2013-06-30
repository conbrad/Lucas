#include "Email.h"

Email::Email()
{
}

EmailHeader::EmailHeader() {

}

EmailHeader::EmailHeader(QString subject, QString sender, QString id) {
    m_subject = subject;
    m_sender = sender;
    m_id = id;
}

QString EmailHeader::getSubject() {
    return m_subject;
}

QString EmailHeader::getSender() {
    return m_sender;
}

QString EmailHeader::getID() {
    return m_id;
}
