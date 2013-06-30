#include "IMAPParser.h"
#include <QRegExp>
#include <QStringList>
#include <QDebug>
#include <QTextStream>

IMAPParser::IMAPParser() {

}

QVector<Folder> IMAPParser::parseFolders(QString data) {
    QVector<Folder> folders;
    QString pattern = "\\* LIST \\(.*\\) \".*\" \"(.*)\"";
    QRegExp re(pattern);
    QStringList lines = data.split(QRegExp("[\r\n]"), QString::SkipEmptyParts);

    for(int i = 0; i < lines.size(); i++) {
        re.indexIn(lines[i]);
        qDebug() << re.cap(1);
        QString folderName = re.cap(1);
        Folder f(folderName);

        if (lines[i].contains("HasChildren")) {
            f.setHasChildren(true);
        }

        folders.push_back(f);
    }
    return folders;
}

int IMAPParser::parseSelect(QString data) {
    int count = 0;
    QStringList lines = data.split(QRegExp("[\r\n]"), QString::SkipEmptyParts);

    QString pattern = "\\* ([0-9]+) EXISTS";
    QRegExp re(pattern);
    for (int i = 0; i < lines.size(); i++) {
        if (re.indexIn(lines[i]) != -1) {
            count = re.cap(1).toInt();
        }
    }
    return count;
}

QVector<EmailHeader> IMAPParser::parseHeaders(QString data) {
    QVector<EmailHeader> headers;
    QString pattern = "\\* ([^\\*]*)";
    QRegExp re(pattern);

    int pos = 0;
    while ((pos = re.indexIn(data, pos)) != -1 ) {
        headers.push_front(parseHeader(re.cap(1)));
        pos += re.matchedLength();
    }
    return headers;
}

EmailHeader IMAPParser::parseHeader(QString data) {
    QStringList lines = data.split(QRegExp("[\r\n]"), QString::SkipEmptyParts);
    QString id, subject, from;

    id = data.split(QRegExp("[^0-9]"))[0];
    for (int i = 0; i < lines.size(); i++) {
        if (lines[i].contains("subject:", Qt::CaseInsensitive)) {
            subject = lines[i].split(QRegExp("[:]"), QString::SkipEmptyParts)[1];
        } else if (lines[i].contains("from:", Qt::CaseInsensitive) ) {
            from = lines[i].split(QRegExp("[:]"), QString::SkipEmptyParts)[1];
        }
    }
    EmailHeader header(subject, from, id);
    return header;
}

QString IMAPParser::parseBody(QString data) {
    QTextStream stream(&data);
    QString header = stream.readLine();
    QString contentID = stream.readLine();
    // Find plain text content
    while (!stream.atEnd() && !stream.readLine().contains("Content-Type: text/plain"));
    while (!stream.atEnd() && stream.readLine() != "");

    // Read content
    QStringList content;
    while (!stream.atEnd()) {
        QString line = stream.readLine();
        if (line == contentID) {
            break;
        } else {
            content << line;
        }
    }
    return content.join("");
}
