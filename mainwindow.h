/*===========================================================================
    SanDic, Sanscrit-English Dictionary
    Copyright (C) 2012-2013 Novikov Artem Gennadievich

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>
===========================================================================*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtSql>
#include <QtWidgets>

#include "config.h"
#include "card.h"
#include "mainwidget.h"
#include "trans.h"
#include "orderdialog.h"

#define CONTRANS(t) connect(t, SIGNAL(UTF8(QString)),   mainWidget, SLOT(setDevaText(QString))); \
                    connect(t, SIGNAL(returnPressed()), mainWidget, SLOT(search()))

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Config*, QSqlDatabase*);

private slots:
    void showDock();
    void wordClicked(QString);
    void changeLang();
    void order() { orderDialog->exec(); }
    void about();

    void loadStyle();
    void setStyle();

private:
    void addDock(QWidget*, QAction*, QString, Qt::DockWidgetArea = Qt::BottomDockWidgetArea);

    void closeEvent(QCloseEvent*);

    bool eventFilter(QObject*, QEvent*);

    QAction* styleAction(QString);

    QHash<QString, QAction*> docks;

    QSqlDatabase* db;
    Config*       config;

    Card* 		  mainCard;
    OrderDialog*  orderDialog;

    QTextEdit*	  abbs;
    QTextEdit*    transMap;
    QStringList	  html; // [0] abbs [1] map

    QActionGroup* stylesGroup;
    QMenu*		  stylesMenu;
};

#endif // MAINWINDOW_H
