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

#include "config.h"

Config::Config() : QSettings(ORGNAME, PROGNAME)
{
    langs.insert("English", "en_EN");
    langs.insert("Russian", "ru_RU");
    lang = value("lang", "English").toString();

    style  = value("style").toString();
    styles = value("styles").toMap();

    if (styles.isEmpty())
        styles[":default"] = readFile(":/rc/default.css");

    if (styles.count() == 1) // или удален последний пользовательский стиль
        style = ":default";

    order = value("order").toMap();

    mainWindowGeometry = value("mainWindowGeometry").toByteArray();
    mainWindowState    = value("mainWindowState").toByteArray();

    cardSize = value("cardSize", QSize(500, 500)).toSize();
}

Config::~Config()
{
    setValue("lang", lang);

    setValue("style",  style);
    setValue("styles", styles);

    setValue("order", order);

    setValue("mainWindowGeometry", mainWindowGeometry);
    setValue("mainWindowState",    mainWindowState);

    setValue("cardSize", cardSize);
}

QString Config::readFile(QString name)
{
    QFile file(name);
    file.open(QFile::ReadOnly);
    return file.readAll();
}
