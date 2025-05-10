/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *preButton;
    QPushButton *newButton;
    QPushButton *nextButton;
    QTableWidget *manager;
    QHBoxLayout *horizontalLayout;
    QPushButton *addButton;
    QPushButton *delButton;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(747, 441);
        gridLayout = new QGridLayout(Widget);
        gridLayout->setObjectName("gridLayout");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        preButton = new QPushButton(Widget);
        preButton->setObjectName("preButton");

        horizontalLayout_2->addWidget(preButton);

        newButton = new QPushButton(Widget);
        newButton->setObjectName("newButton");

        horizontalLayout_2->addWidget(newButton);

        nextButton = new QPushButton(Widget);
        nextButton->setObjectName("nextButton");

        horizontalLayout_2->addWidget(nextButton);


        gridLayout->addLayout(horizontalLayout_2, 2, 0, 1, 1);

        manager = new QTableWidget(Widget);
        manager->setObjectName("manager");

        gridLayout->addWidget(manager, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        addButton = new QPushButton(Widget);
        addButton->setObjectName("addButton");

        horizontalLayout->addWidget(addButton);

        delButton = new QPushButton(Widget);
        delButton->setObjectName("delButton");

        horizontalLayout->addWidget(delButton);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        preButton->setText(QCoreApplication::translate("Widget", "\344\270\212\344\270\200\351\241\265", nullptr));
        newButton->setText(QCoreApplication::translate("Widget", "\345\210\233\345\273\272\346\226\260\351\241\265", nullptr));
        nextButton->setText(QCoreApplication::translate("Widget", "\344\270\213\344\270\200\351\241\265", nullptr));
        addButton->setText(QCoreApplication::translate("Widget", "\346\267\273\345\212\240", nullptr));
        delButton->setText(QCoreApplication::translate("Widget", "\345\210\240\351\231\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
