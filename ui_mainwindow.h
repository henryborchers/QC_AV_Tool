/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen_Folder;
    QAction *actionExit;
    QAction *actionAdd_Row;
    QAction *actionTest;
    QAction *actionRemove_Row;
    QAction *actionAbout;
    QAction *actionSet_All_Items_as_Done;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QTreeView *FilesView;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QLabel *lbl_fileName;
    QLineEdit *le_fileName;
    QTabWidget *tabWidget;
    QWidget *tab_moreinfo;
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QFormLayout *formLayout;
    QLabel *label_4;
    QLineEdit *lineEdit_3;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QLabel *label_5;
    QLineEdit *lineEdit_8;
    QLabel *label_6;
    QLineEdit *lineEdit_5;
    QLabel *label_7;
    QLineEdit *lineEdit_6;
    QLabel *label;
    QLineEdit *lineEdit;
    QLabel *label_8;
    QLineEdit *lineEdit_7;
    QLineEdit *lineEdit_4;
    QLabel *label_3;
    QGroupBox *groupBox_2;
    QFormLayout *formLayout_2;
    QLabel *label_9;
    QLineEdit *lineEdit_9;
    QLabel *label_10;
    QLineEdit *lineEdit_10;
    QLabel *label_11;
    QLineEdit *lineEdit_11;
    QLabel *label_12;
    QLineEdit *lineEdit_12;
    QLabel *label_13;
    QLineEdit *lineEdit_13;
    QLabel *label_14;
    QLineEdit *lineEdit_14;
    QLabel *label_15;
    QLineEdit *lineEdit_15;
    QLineEdit *lineEdit_16;
    QLabel *label_16;
    QWidget *tab_validation;
    QLabel *label_17;
    QWidget *tab_comments;
    QVBoxLayout *verticalLayout_2;
    QTextEdit *textEdit;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(868, 886);
        MainWindow->setMinimumSize(QSize(500, 300));
        actionOpen_Folder = new QAction(MainWindow);
        actionOpen_Folder->setObjectName(QStringLiteral("actionOpen_Folder"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionAdd_Row = new QAction(MainWindow);
        actionAdd_Row->setObjectName(QStringLiteral("actionAdd_Row"));
        actionTest = new QAction(MainWindow);
        actionTest->setObjectName(QStringLiteral("actionTest"));
        actionRemove_Row = new QAction(MainWindow);
        actionRemove_Row->setObjectName(QStringLiteral("actionRemove_Row"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionSet_All_Items_as_Done = new QAction(MainWindow);
        actionSet_All_Items_as_Done->setObjectName(QStringLiteral("actionSet_All_Items_as_Done"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setMinimumSize(QSize(0, 0));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        FilesView = new QTreeView(centralWidget);
        FilesView->setObjectName(QStringLiteral("FilesView"));

        verticalLayout->addWidget(FilesView);

        frame = new QFrame(centralWidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 5, -1, 0);
        lbl_fileName = new QLabel(frame);
        lbl_fileName->setObjectName(QStringLiteral("lbl_fileName"));

        horizontalLayout->addWidget(lbl_fileName);

        le_fileName = new QLineEdit(frame);
        le_fileName->setObjectName(QStringLiteral("le_fileName"));
        le_fileName->setReadOnly(true);

        horizontalLayout->addWidget(le_fileName);


        verticalLayout->addWidget(frame);

        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setMaximumSize(QSize(16777215, 300));
        tab_moreinfo = new QWidget();
        tab_moreinfo->setObjectName(QStringLiteral("tab_moreinfo"));
        gridLayout = new QGridLayout(tab_moreinfo);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        groupBox = new QGroupBox(tab_moreinfo);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        formLayout = new QFormLayout(groupBox);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_4);

        lineEdit_3 = new QLineEdit(groupBox);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setReadOnly(true);

        formLayout->setWidget(2, QFormLayout::FieldRole, lineEdit_3);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_2);

        lineEdit_2 = new QLineEdit(groupBox);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setReadOnly(true);

        formLayout->setWidget(3, QFormLayout::FieldRole, lineEdit_2);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_5);

        lineEdit_8 = new QLineEdit(groupBox);
        lineEdit_8->setObjectName(QStringLiteral("lineEdit_8"));
        lineEdit_8->setReadOnly(true);

        formLayout->setWidget(4, QFormLayout::FieldRole, lineEdit_8);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));

        formLayout->setWidget(5, QFormLayout::LabelRole, label_6);

        lineEdit_5 = new QLineEdit(groupBox);
        lineEdit_5->setObjectName(QStringLiteral("lineEdit_5"));
        lineEdit_5->setReadOnly(true);

        formLayout->setWidget(5, QFormLayout::FieldRole, lineEdit_5);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QStringLiteral("label_7"));

        formLayout->setWidget(6, QFormLayout::LabelRole, label_7);

        lineEdit_6 = new QLineEdit(groupBox);
        lineEdit_6->setObjectName(QStringLiteral("lineEdit_6"));
        lineEdit_6->setReadOnly(true);

        formLayout->setWidget(6, QFormLayout::FieldRole, lineEdit_6);

        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(7, QFormLayout::LabelRole, label);

        lineEdit = new QLineEdit(groupBox);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setReadOnly(true);

        formLayout->setWidget(7, QFormLayout::FieldRole, lineEdit);

        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QStringLiteral("label_8"));

        formLayout->setWidget(8, QFormLayout::LabelRole, label_8);

        lineEdit_7 = new QLineEdit(groupBox);
        lineEdit_7->setObjectName(QStringLiteral("lineEdit_7"));
        lineEdit_7->setReadOnly(true);

        formLayout->setWidget(8, QFormLayout::FieldRole, lineEdit_7);

        lineEdit_4 = new QLineEdit(groupBox);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));
        lineEdit_4->setReadOnly(true);

        formLayout->setWidget(1, QFormLayout::FieldRole, lineEdit_4);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_3);


        gridLayout->addWidget(groupBox, 0, 1, 1, 1);

        groupBox_2 = new QGroupBox(tab_moreinfo);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        formLayout_2 = new QFormLayout(groupBox_2);
        formLayout_2->setSpacing(6);
        formLayout_2->setContentsMargins(11, 11, 11, 11);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName(QStringLiteral("label_9"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_9);

        lineEdit_9 = new QLineEdit(groupBox_2);
        lineEdit_9->setObjectName(QStringLiteral("lineEdit_9"));
        lineEdit_9->setReadOnly(true);

        formLayout_2->setWidget(2, QFormLayout::FieldRole, lineEdit_9);

        label_10 = new QLabel(groupBox_2);
        label_10->setObjectName(QStringLiteral("label_10"));

        formLayout_2->setWidget(3, QFormLayout::LabelRole, label_10);

        lineEdit_10 = new QLineEdit(groupBox_2);
        lineEdit_10->setObjectName(QStringLiteral("lineEdit_10"));
        lineEdit_10->setReadOnly(true);

        formLayout_2->setWidget(3, QFormLayout::FieldRole, lineEdit_10);

        label_11 = new QLabel(groupBox_2);
        label_11->setObjectName(QStringLiteral("label_11"));

        formLayout_2->setWidget(4, QFormLayout::LabelRole, label_11);

        lineEdit_11 = new QLineEdit(groupBox_2);
        lineEdit_11->setObjectName(QStringLiteral("lineEdit_11"));
        lineEdit_11->setReadOnly(true);

        formLayout_2->setWidget(4, QFormLayout::FieldRole, lineEdit_11);

        label_12 = new QLabel(groupBox_2);
        label_12->setObjectName(QStringLiteral("label_12"));

        formLayout_2->setWidget(5, QFormLayout::LabelRole, label_12);

        lineEdit_12 = new QLineEdit(groupBox_2);
        lineEdit_12->setObjectName(QStringLiteral("lineEdit_12"));
        lineEdit_12->setReadOnly(true);

        formLayout_2->setWidget(5, QFormLayout::FieldRole, lineEdit_12);

        label_13 = new QLabel(groupBox_2);
        label_13->setObjectName(QStringLiteral("label_13"));

        formLayout_2->setWidget(6, QFormLayout::LabelRole, label_13);

        lineEdit_13 = new QLineEdit(groupBox_2);
        lineEdit_13->setObjectName(QStringLiteral("lineEdit_13"));
        lineEdit_13->setReadOnly(true);

        formLayout_2->setWidget(6, QFormLayout::FieldRole, lineEdit_13);

        label_14 = new QLabel(groupBox_2);
        label_14->setObjectName(QStringLiteral("label_14"));

        formLayout_2->setWidget(7, QFormLayout::LabelRole, label_14);

        lineEdit_14 = new QLineEdit(groupBox_2);
        lineEdit_14->setObjectName(QStringLiteral("lineEdit_14"));
        lineEdit_14->setReadOnly(true);

        formLayout_2->setWidget(7, QFormLayout::FieldRole, lineEdit_14);

        label_15 = new QLabel(groupBox_2);
        label_15->setObjectName(QStringLiteral("label_15"));

        formLayout_2->setWidget(8, QFormLayout::LabelRole, label_15);

        lineEdit_15 = new QLineEdit(groupBox_2);
        lineEdit_15->setObjectName(QStringLiteral("lineEdit_15"));
        lineEdit_15->setReadOnly(true);

        formLayout_2->setWidget(8, QFormLayout::FieldRole, lineEdit_15);

        lineEdit_16 = new QLineEdit(groupBox_2);
        lineEdit_16->setObjectName(QStringLiteral("lineEdit_16"));
        lineEdit_16->setReadOnly(true);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, lineEdit_16);

        label_16 = new QLabel(groupBox_2);
        label_16->setObjectName(QStringLiteral("label_16"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_16);


        gridLayout->addWidget(groupBox_2, 0, 2, 1, 1);

        tabWidget->addTab(tab_moreinfo, QString());
        tab_validation = new QWidget();
        tab_validation->setObjectName(QStringLiteral("tab_validation"));
        label_17 = new QLabel(tab_validation);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(220, 80, 251, 16));
        tabWidget->addTab(tab_validation, QString());
        tab_comments = new QWidget();
        tab_comments->setObjectName(QStringLiteral("tab_comments"));
        verticalLayout_2 = new QVBoxLayout(tab_comments);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        textEdit = new QTextEdit(tab_comments);
        textEdit->setObjectName(QStringLiteral("textEdit"));

        verticalLayout_2->addWidget(textEdit);

        tabWidget->addTab(tab_comments, QString());

        verticalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 868, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        mainToolBar->setMovable(false);
        mainToolBar->setFloatable(true);
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
#ifndef QT_NO_SHORTCUT
        lbl_fileName->setBuddy(le_fileName);
#endif // QT_NO_SHORTCUT

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionOpen_Folder);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuHelp->addSeparator();
        menuHelp->addAction(actionAbout);
        mainToolBar->addAction(actionOpen_Folder);
        mainToolBar->addAction(actionAdd_Row);
        mainToolBar->addAction(actionRemove_Row);
        mainToolBar->addAction(actionTest);
        mainToolBar->addAction(actionSet_All_Items_as_Done);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionOpen_Folder->setText(QApplication::translate("MainWindow", "Open Folder...", 0));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", 0));
        actionAdd_Row->setText(QApplication::translate("MainWindow", "Add Row", 0));
        actionTest->setText(QApplication::translate("MainWindow", "Test", 0));
        actionRemove_Row->setText(QApplication::translate("MainWindow", "Remove Row", 0));
        actionAbout->setText(QApplication::translate("MainWindow", "About", 0));
        actionSet_All_Items_as_Done->setText(QApplication::translate("MainWindow", "Set All Items as Done", 0));
        lbl_fileName->setText(QApplication::translate("MainWindow", "File Name", 0));
        le_fileName->setText(QApplication::translate("MainWindow", "sdfdsfdsfsdf", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Technical Metadata", 0));
        label_4->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        label_2->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        label_5->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        label_6->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        label_7->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        label->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        label_8->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        label_3->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Other Data", 0));
        label_9->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        label_10->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        label_11->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        label_12->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        label_13->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        label_14->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        label_15->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        label_16->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_moreinfo), QApplication::translate("MainWindow", "More Information", 0));
        label_17->setText(QApplication::translate("MainWindow", "Put something here", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_validation), QApplication::translate("MainWindow", "Validation", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_comments), QApplication::translate("MainWindow", "Comments", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
