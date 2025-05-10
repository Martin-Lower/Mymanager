#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QEvent>
#include <QMouseEvent>
#include <QMenu>
#include <QMessageBox>
#include <QDebug>
#include <QTimer>
#include <QStackedWidget>
#include <QPushButton>
#include <QTableWidget>
#include <QHeaderView>
#include <QStandardPaths>
#include <QDir>

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

#include "additemdialog.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

public:
    void initDatabase();            // 初始化数据库
    void initWindows();             // 初始化窗口
    void initWidget();              // 初始化表格
    void loadTasks();               // 加载数据

protected:
    // 重写鼠标事件以实现拖拽效果
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private slots:
    void addItems();                // 添加数据
    void delItems();                // 删除数据

    void nextPage();                // 下一页
    void prevPage();                // 上一页
    void addNewPage();              // 增加一页

private:
    Ui::Widget *ui;

    // 数据库相关变量
    QSqlDatabase db;
    QSqlQuery query;

    // 窗口相关变量
    QTableWidget* manager;
    QPushButton* addButton;
    QPushButton* delButton;
    QPushButton* nextButton;
    QPushButton* preButton;
    QPushButton* newButton;

    QWidget *dragBar;
    QPoint dragPos;
    QStackedWidget *stackedWidget;
    int currentPage = 0;

    // 插入信息框相关变量
    addItemdialog* dlg;
    int count;

};

#endif // WIDGET_H
