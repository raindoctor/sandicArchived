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

#ifndef CARD_H
#define CARD_H

#include <QtSql>
#include <QtWidgets>

#include "config.h"

struct AbbItem
{
    AbbItem(QString abb, QString desc)
        : rx(QRegExp("(^|\\W)(" + QRegExp::escape(abb) + ")(\\W|$)")),
          desc(desc.replace("'", "′")) { }

    QRegExp rx;
    QString desc;
};


class Card : public QTextEdit
{
    Q_OBJECT

public:
    Card(Card*);
    Card(Config*, QSqlDatabase*);

public slots:
    void article(QString, QString = "");

private:
    void resizeEvent(QResizeEvent*);

    QString buildRec(QString, QList<QStringList>);
    QString buildList(QStringList);

    QSqlDatabase* db;
    Config*		  config;

    QMap<QString, QList<AbbItem> > abbs;
};

#endif // CARD_H
