#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , longPressTimer(new QTimer(this))
{
    //QTimer *longPressTimer = new QTimer(this);
    ui->setupUi(this);
    longPressTimer->setInterval(500);  // 设置长按时间为500ms
    longPressTimer->setSingleShot(true);  // 只触发一次

    // 连接按钮按下和释放的信号
    connect(ui->pushButton_sleep, &QPushButton::pressed, this, &MainWindow::handleButtonPressed);
    connect(ui->pushButton_sleep, &QPushButton::released, this, &MainWindow::handleButtonReleased);
    connect(longPressTimer, &QTimer::timeout, this, &MainWindow::onLongPressTriggered);
}

void MainWindow::handleButtonPressed()
{
    isLongPressing = false;  // 重置长按状态
    longPressTimer->start();  // 启动定时器
}

void MainWindow::handleButtonReleased()
{
    longPressTimer->stop();  // 停止定时器

    if (!isLongPressing) {
        // 如果未进入长按状态，则认为是短按
        qDebug() << "Short Click Detected";
    }
}

void MainWindow::onLongPressTriggered()
{
    isLongPressing = true;  // 标记为长按状态
    qDebug() << "Long Press Detected";
    longPressTimer->start(500);  // 重新启动定时器，持续触发长按效果
}


MainWindow::~MainWindow()
{
    delete ui;
}

