#ifndef ADDITEMDIALOG_H
#define ADDITEMDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QFormLayout>
#include <QSpinBox>
#include <QDateEdit>
#include <QComboBox>

class addItemdialog : public QDialog
{
    Q_OBJECT
public:
    explicit addItemdialog(QWidget *parent = nullptr);

    // 获取用户输入的数据
    QString prio() const;
    QString name() const;
    QString desc() const;
    QString starttime() const;
    QString endtime() const;
    QString remind() const;
    QString opin() const;

private:
    QSpinBox *prioritySpinBox; // 优先级输入框
    QLineEdit *nameEdit;       // 名称输入框
    QLineEdit *descEdit;       // 描述输入框
    QDateEdit *startDateEdit;  // 起始时间
    QDateEdit *endDateEdit;    // 结束时间
    QComboBox *remindEdit;     // 提醒输入框
    QLineEdit *opinEdit;       // 意见输入框
signals:
};

#endif // ADDITEMDIALOG_H
