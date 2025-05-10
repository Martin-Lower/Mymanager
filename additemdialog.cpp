#include "additemdialog.h"

addItemdialog::addItemdialog(QWidget *parent)
    : QDialog{parent}
{
    //设置标题
    setWindowTitle("添加任务");

    // 任务优先级控件
    prioritySpinBox = new QSpinBox(this);
    prioritySpinBox->setRange(1, 5); // 设置优先级范围
    // 任务名称控件
    nameEdit = new QLineEdit(this);
    // 任务描述控件
    descEdit = new QLineEdit(this);
    // 任务开始时间控件
    startDateEdit = new QDateEdit(QDate::currentDate(), this);
    startDateEdit->setDisplayFormat("yyyy-MM-dd");  // 设置日期格式
    startDateEdit->setCalendarPopup(true);          // 允许弹出日历
    // 任务结束时间控件
    endDateEdit = new QDateEdit(QDate::currentDate().addDays(7), this);
    endDateEdit->setDisplayFormat("yyyy-MM-dd");
    endDateEdit->setCalendarPopup(true);
    // 任务提醒控件
    remindEdit = new QComboBox(this);
    remindEdit->addItem("闹钟提醒");

    // remindEdit->addItem();  这里可以重复添加选项，目前只提供一个，到时候学学如何开放闹钟接口

    // 任务吐槽控件
    opinEdit = new QLineEdit(this);


    // 创建按钮
    QPushButton *okButton = new QPushButton("OK", this);
    QPushButton *cancelButton = new QPushButton("Cancel", this);

    // 连接按钮信号
    connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);

    // 布局
    QFormLayout *formLayout = new QFormLayout(this);
    formLayout->addRow("任务优先级:", prioritySpinBox);
    formLayout->addRow("任务名称:", nameEdit);
    formLayout->addRow("任务描述:", descEdit);
    formLayout->addRow("任务起始时间:", startDateEdit);
    formLayout->addRow("任务结束时间:", endDateEdit);
    formLayout->addRow("任务提醒:", remindEdit);
    formLayout->addRow("任务吐槽:", opinEdit);
    formLayout->addRow(okButton, cancelButton);

}


QString addItemdialog::prio() const
{
    return prioritySpinBox->text();
}

QString addItemdialog::name() const
{
    return nameEdit->text();
}

QString addItemdialog::desc() const
{
    return descEdit->text();
}
QString addItemdialog::starttime() const {
    return startDateEdit->date().toString("M/d/yy");
}

QString addItemdialog::endtime() const {
    return endDateEdit->date().toString("M/d/yy");
}

QString addItemdialog::remind() const
{
    return remindEdit->currentText();
}

QString addItemdialog::opin() const
{
    return opinEdit->text();
}


