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

#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QtSql>
#include <QtWidgets>

#include "config.h"

#include "ui_mainwidget.h"

#define GETWORD(i) i.sibling(i.row(), 1).isValid() ? \
                   i.sibling(i.row(), 0).data().toString() : \
                   i.data().toString()

class ItemDelegate : public QItemDelegate
{
public:
    void paint(QPainter*, const QStyleOptionViewItem&, const QModelIndex&) const;
};


class MainWidget : public QWidget, private Ui::MainWidget
{
    Q_OBJECT

public:
    MainWidget(Config*, QSqlDatabase*);

signals:
    void wordChanged(QString, QString);
    void wordClicked(QString);

private slots:
    void addDevaChar(QChar ch)    { tabWidget->currentIndex() ? searchCombo->lineEdit()->insert(ch) :
                                                                indexCombo->lineEdit()->insert(ch); }
    void setDevaText(QString txt) { tabWidget->currentIndex() ? searchCombo->lineEdit()->setText(txt) :
                                                                indexCombo->lineEdit()->setText(txt); }

    void rowChanged(const QModelIndex&, const QModelIndex&);

    void clicked(QModelIndex index);
    void doubleClicked(QModelIndex index);

    void editTextChanged(const QString&);

    void search();

private:
    bool eventFilter(QObject*, QEvent*);

    QSqlDatabase* db;
    Config* 	  config;
};

#endif // MAINWIDGET_H
