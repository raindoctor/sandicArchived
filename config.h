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

#ifndef CONFIG_H
#define CONFIG_H

#include <QtWidgets>

#define ORGNAME  "NovikovAG"

#define PROGNAME "SanDic"
#define VERSION  "2.5"

#if defined(Q_OS_MAC)
    #include <CoreFoundation/CoreFoundation.h>
#endif

class Config : public QSettings
{
public:
    Config();
   ~Config();

    QString				    lang;
    QMap<QString, QString>  langs;

    QString					style;
    QMap<QString, QVariant> styles;

    QStringList				originKeys;
    QString					originSuff;
    QMap<QString, QVariant> order;

    QByteArray  mainWindowGeometry;
    QByteArray  mainWindowState;

    QSize	 	cardSize;

    QString readFile(QString);
};

#endif // CONFIG_H
