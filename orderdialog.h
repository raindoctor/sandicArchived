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

#ifndef ORDERDIALOG_H
#define ORDERDIALOG_H

#include <QtSql>
#include <QtWidgets>

#include "config.h"

#include "ui_orderdialog.h"

class OrderDialog : public QDialog, private Ui::OrderDialog
{
    Q_OBJECT
    
public:
    OrderDialog(Config*, QSqlDatabase*);

private:
    void closeEvent(QCloseEvent*);

    void addItem(QString, bool = true);
    void setOrigins();

    QSqlDatabase* db;
    Config* 	  config;
};

#endif // ORDERDIALOG_H
