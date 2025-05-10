#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)

{
    ui->setupUi(this);

    //连接数据库
    QMessageBox::information(this,"提示","正在连接数据库");

    db = QSqlDatabase::addDatabase("QSQLITE");
    QString dbDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(dbDir);
    QString dbPath = dbDir + "/task.db";
    db.setDatabaseName(dbPath);
    query = QSqlQuery(db);

    // qDebug() << "数据库路径:" << QDir::toNativeSeparators(dbPath);

    if(!db.open()){
        QSqlError e = db.lastError();
        QString s = "文件没有正确打开:";
        s.append(e.text());
        QMessageBox::warning(this,"提示",s);
        qFatal("致命错误发生");  // 这里后续改成主程序接口捕获错误*******************
    }
    else{
        QMessageBox::information(this,"提示","数据库连接成功");
    }
    // 创建数据库，如果没有就创建一个
    query.exec("CREATE TABLE IF NOT EXISTS task ("
               "name TEXT PRIMARY KEY NOT NULL, "  // 主键，不能为空
               "prio TEXT, "
               "description TEXT, "
               "start_time TEXT, "
               "end_time TEXT, "
               "reminder_method TEXT, "
               "review TEXT)");



    // 初始化窗口

    setFixedSize(800,500);// 设置窗口大小
    setWindowFlags(Qt::Tool | Qt::FramelessWindowHint);// 隐藏任务栏 去除边框
    setAttribute(Qt::WA_TranslucentBackground);   // 背景透明

    // 添加透明拖拽条（高度30px，覆盖顶部）
    dragBar = new QWidget(this);
    dragBar->setFixedHeight(18);
    dragBar->setStyleSheet("background-color: transparent;");
    dragBar->move(0, 0);
    dragBar->resize(width(), 30);

    // 确保拖拽条在最上层
    dragBar->raise();


    // 初始化表格
    initWidget();

    // 加载数据
    loadTasks();

    // 连接按钮的信号与槽： 增删数据
    ui->addButton->setStyleSheet("QPushButton{background-color: rgba(255, 255, 255, 50%);}");
    ui->delButton->setStyleSheet("QPushButton{background-color: rgba(255, 255, 255, 50%);}");

    ui->nextButton->setStyleSheet("QPushButton{background-color: rgba(255, 255, 255, 50%);}");
    ui->preButton->setStyleSheet("QPushButton{background-color: rgba(255, 255, 255, 50%);}");
    ui->nextButton->hide();
    ui->preButton->hide();
    ui->newButton->hide();
    // 等我实现了多页操作再显示出来吧
    connect(ui->addButton,&QPushButton::clicked,this,&Widget::addItems);
    connect(ui->delButton,&QPushButton::clicked,this,&Widget::delItems);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::initWidget()
{
    //设置属性列
    ui->manager->setColumnCount(6);
    QStringList horizontalList;
    horizontalList << "优先级";
    horizontalList << "任务名称";
    horizontalList << "任务描述";
    horizontalList << "起止时间";
    horizontalList << "提醒方式";
    horizontalList << "吐槽";
    ui->manager->setHorizontalHeaderLabels(horizontalList);
    // 水平拉伸方式
    ui->manager->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    // ui->manager->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    // 禁用水平表头的交互（包括悬停、点击效果）
    ui->manager->horizontalHeader()->setSectionsClickable(false);
    ui->manager->horizontalHeader()->setHighlightSections(false);
    // 实际上，把拖拽条的像素调大点就行了

    // 禁止内容省略
    ui->manager->setTextElideMode(Qt::ElideNone);
    ui->manager->setWordWrap(true);
    // 禁止用户操作
    ui->manager->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // 修改样式表
    // 设置整个QTableWidget半透明（包括背景、表头、单元格）
    ui->manager->setStyleSheet(
        "QTableWidget {"
        "   background-color: rgba(255, 255, 255, 20%);"  // 白色背景，50%透明度
        "   gridline-color: rgba(0, 0, 0, 30%);"         // 网格线透明度
        "}"
        "QHeaderView::section {"
        "   background-color: rgba(200, 200, 200, 20%);"  // 表头部分透明度
        "}"
        );

    ui->manager->setAttribute(Qt::WA_StyledBackground, true);  // 关键！

    // 获取新的数据后要重新按照优先级排序
    ui->manager->sortItems(0, Qt::DescendingOrder);

}

void Widget::loadTasks()
{
    // 清空现有内容
    ui->manager->setRowCount(0);

    QSqlQuery query;
    if (!query.exec("SELECT prio, name, description, start_time, end_time, reminder_method, review FROM task")) {
        QMessageBox::critical(this, "错误", "查询失败: " + query.lastError().text());
        return;
    }

    int row = 0;
    while (query.next()) {
        // 添加新行
        ui->manager->insertRow(row);

        // 获取数据
        QString prio = query.value("prio").toString();
        QString name = query.value("name").toString();
        QString desc = query.value("description").toString();
        QString start = query.value("start_time").toString();
        QString end = query.value("end_time").toString();
        QString remind = query.value("reminder_method").toString();
        QString review = query.value("review").toString();

        // 设置表格项
        ui->manager->setItem(row, 0, new QTableWidgetItem(prio));
        ui->manager->setItem(row, 1, new QTableWidgetItem(name));
        ui->manager->setItem(row, 2, new QTableWidgetItem(desc));

        // 合并开始和结束时间
        QString timeRange = start + " - " + end;
        ui->manager->setItem(row, 3, new QTableWidgetItem(timeRange));

        ui->manager->setItem(row, 4, new QTableWidgetItem(remind));
        ui->manager->setItem(row, 5, new QTableWidgetItem(review));

        row++;
    }

    // 获取新的数据后要重新按照优先级排序
    ui->manager->sortItems(0, Qt::DescendingOrder);
}

void Widget::delItems()
{
    int pickRow = ui->manager->currentRow();
    if(pickRow>=0){
        QTableWidgetItem* timeItem = ui->manager->item(pickRow,1);
        if(!timeItem){
            QMessageBox::warning(this,"警告","无法获取值");
            return;
        }
        // 这里是为了数据库操作便利，name是主键
        QString name = timeItem->text();
        QString sql = "delete from task where name = :name";
        query.prepare(sql);
        query.bindValue(":name",name);
        db.transaction();
        bool flag = query.exec();
        if(flag){
            QMessageBox::information(this,"提示","删除成功！");
            ui->manager->removeRow(pickRow);
            db.commit();
        }else{
            QMessageBox::information(this,"提示","删除失败"+query.lastError().text());
            db.rollback();
        }

    }
    else{
        QMessageBox::warning(this,"警告","你没有选中任何一行");
    }
}

void Widget::nextPage()
{

}

void Widget::prevPage()
{

}

void Widget::addNewPage()
{

}

// 鼠标按下时记录位置
void Widget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && dragBar->geometry().contains(event->pos())) {
        dragPos = event->globalPosition().toPoint() - frameGeometry().topLeft();
        event->accept();
    } else {
        event->ignore();  // 其他区域事件传递给子控件
    }
}
// 鼠标移动时拖动窗口
void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton && !dragPos.isNull()) {
        move(event->globalPosition().toPoint() - dragPos);
        event->accept();
    }
}


void Widget::addItems()
{
    //创建对话框
    dlg = new addItemdialog(this);

    dlg->setFixedSize(600,270);
    if (dlg->exec() == QDialog::Accepted) {
        // 获取对话框中的数据
        count = ui->manager->rowCount();
        ui->manager->setRowCount(count+1);
        QTableWidgetItem *prio = new QTableWidgetItem(dlg->prio());
        QTableWidgetItem *name = new QTableWidgetItem(dlg->name());
        QTableWidgetItem *desc =  new QTableWidgetItem(dlg->desc());
        QTableWidgetItem *start = new QTableWidgetItem(dlg->starttime());
        QTableWidgetItem *end = new QTableWidgetItem(dlg->endtime());
        QString s = start->text()+"-"+end->text();
        QTableWidgetItem *time = new QTableWidgetItem(s);
        QTableWidgetItem *remind = new QTableWidgetItem(dlg->remind());
        QTableWidgetItem *opin = new QTableWidgetItem(dlg->opin());
        ui->manager->setItem(count,0,prio);
        ui->manager->setItem(count,1,name);
        ui->manager->setItem(count,2,desc);
        ui->manager->setItem(count,3,time);
        ui->manager->setItem(count,4,remind);
        ui->manager->setItem(count,5,opin);

        ui->manager->resizeRowToContents(5);
        QTimer::singleShot(100, [=]() {
            int totalWidth = 0;
            for (int i = 0; i < ui->manager->columnCount(); ++i) {
                totalWidth += ui->manager->columnWidth(i);
            }

            // 如果内容宽度不足表格宽度，则启用拉伸
            if (totalWidth < ui->manager->viewport()->width()) {
                ui->manager->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            }
        });

        // 获取新的数据后要重新按照优先级排序
        ui->manager->sortItems(0, Qt::DescendingOrder);

        //获取数据给数据库发过去

        // 检查数据库连接
        if (!db.isOpen()) {
            QMessageBox::critical(this, "错误", "数据库未连接");
            return;
        }

        // 准备 SQL 语句
        QString sql = "INSERT INTO task (prio, name, description, start_time, end_time, reminder_method, review) VALUES (:prio, :name, :description, :start_time, :end_time, :reminder_method, :review)";
        query.prepare(sql);

        // 绑定参数
        query.bindValue(":prio", prio->text());
        query.bindValue(":name", name->text());
        query.bindValue(":description", desc->text());
        query.bindValue(":start_time", start->text());
        query.bindValue(":end_time", start->text());
        query.bindValue(":reminder_method", remind->text());
        query.bindValue(":review", opin->text());

        // 开启事务
        db.transaction();

        // 执行 SQL 语句
        bool flag = query.exec();

        if (flag) {
            QMessageBox::information(this, "提示", "插入信息成功！");
            db.commit(); // 提交事务
        } else {
            QMessageBox::information(this, "提示", "插入失败: " + query.lastError().text());
            db.rollback(); // 回滚事务
        }

    }

}
