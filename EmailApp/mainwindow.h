#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "IMAPClient.h"
#include "QTreeWidget"
#include "QListWidget"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
    IMAPClient emailClient;
    QString m_email;

    void setupFolderWidget();
    void setupEmailListWidget();
    void addFolderChildren(QTreeWidgetItem* parent, QVector<Folder>& folders);

private slots:
    void onFolderClick(QTreeWidgetItem* item, int value);
    void onEmailClick(QListWidgetItem* item);
};

#endif // MAINWINDOW_H
