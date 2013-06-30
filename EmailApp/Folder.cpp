#include "Folder.h"

Folder::Folder() {

}

Folder::Folder(QString name) {
    m_name = name;
    m_hasChildren = false;
}

QString Folder::getName() {
    return m_name;
}

void Folder::addChild(Folder child) {
    m_children.push_back(child);
}

QVector<Folder> Folder::getChildren() {
    return m_children;
}

void Folder::setChildren(QVector<Folder> children) {
    m_children = children;
}

bool Folder::hasChildren() {
    return m_hasChildren;
}

void Folder::setHasChildren(bool value) {
    m_hasChildren = value;
}
