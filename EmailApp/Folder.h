#ifndef FOLDER_H
#define FOLDER_H

#include <QVector>
#include <QString>

class Folder {

public:
    Folder();
    Folder(QString name);
    QString getName();
    void addChild(Folder child);
    QVector<Folder> getChildren();
    void setChildren(QVector<Folder> children);
    bool hasChildren();
    void setHasChildren(bool value);
private:
    QString m_name;
    QVector<Folder> m_children;
    bool m_hasChildren;
};

#endif
