#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Folder.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), emailClient("imap.gmail.com", 993),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_email = "lucas.cmpt212@gmail.com";
    emailClient.connectToHost(m_email, "1lucas23");
    setupFolderWidget();
    setupEmailListWidget();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupFolderWidget() {
    QVector<Folder> folders = emailClient.getFolders();
    QTreeWidget* folderWidget = ui->folderWidget;
    folderWidget->setHeaderLabel(m_email);
    connect(folderWidget, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(onFolderClick(QTreeWidgetItem*,int)));
    addFolderChildren(nullptr, folders);
}

void MainWindow::addFolderChildren(QTreeWidgetItem* parent, QVector<Folder>& folders) {
    QTreeWidget* folderWidget = ui->folderWidget;
    for (int i = 0; i < folders.size(); i++) {
        QString name = folders[i].getName();
        QTreeWidgetItem* item = new QTreeWidgetItem(QStringList(folders[i].getName()));
        if (parent == nullptr) {
            folderWidget->addTopLevelItem(item);
        } else {
            parent->addChild(item);
        }

        if (folders[i].hasChildren()) {
            addFolderChildren(item, folders[i].getChildren());
        }
    }
}

void MainWindow::setupEmailListWidget() {
    connect(ui->emailListWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(onEmailClick(QListWidgetItem*)));
}

void MainWindow::onFolderClick(QTreeWidgetItem *item, int value) {
    QString folderName = item->text(value);
    QVector<EmailHeader> headers = emailClient.getNewestEmailHeaders(folderName);
    ui->emailListWidget->clear();

    for (int i = 0; i < headers.size(); i++) {
        QString label = QString("%1. %2 - %3").arg(headers[i].getID(), headers[i].getSubject(), headers[i].getSender());
        ui->emailListWidget->addItem(label);
    }
}

void MainWindow::onEmailClick(QListWidgetItem* item) {
    QString label = item->text();
    QString id = label.split(QRegExp("[^0-9]"), QString::SkipEmptyParts)[0];
    ui->emailWidget->setText(emailClient.getEmailContent(id));
}

