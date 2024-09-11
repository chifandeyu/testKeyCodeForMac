#include "mainwindow.h"
#include <Cocoa/Cocoa.h>
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 在 macOS 上使用 NSEvent 监听键盘事件
#ifdef Q_OS_MAC
    [NSEvent addLocalMonitorForEventsMatchingMask:NSEventMaskKeyDown handler:^NSEvent * (NSEvent *event) {
                                              if ([event modifierFlags] & NSEventModifierFlagCommand) {
                                                  // 检查按下的键是否是 Insert 键 (macOS 没有直接的 Insert 键，通常使用 F13 代替)
                                                  if ([[event charactersIgnoringModifiers] isEqualToString:@"\uF710"]) { // \uF710 对应 F13 键
                                                      qDebug() << "Insert key pressed";
                                                  }
                                              }
                                              return event;
                                          }];

    [NSEvent addLocalMonitorForEventsMatchingMask:NSEventMaskKeyUp handler:^NSEvent * (NSEvent *event) {
                                              if ([event modifierFlags] & NSEventModifierFlagCommand) {
                                                  // 检查释放的键是否是 Insert 键
                                                  if ([[event charactersIgnoringModifiers] isEqualToString:@"\uF710"]) {
                                                      qDebug() << "Insert key released";
                                                  }
                                              }
                                              return event;
                                          }];
#endif
}

MainWindow::~MainWindow()
{
    delete ui;
}
