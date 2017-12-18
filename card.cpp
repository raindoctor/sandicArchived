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

#include "card.h"

Card::Card(Card* card) : config(card->config)
{
    setWindowTitle(card->windowTitle());
//    setHtml(card->toHtml());
    setDocument(card->document()->clone());
    setReadOnly(true);

    resize(config->cardSize);
}

Card::Card(Config* config, QSqlDatabase* db)
    : db(db), config(config)
{
    QSqlQuery query("SELECT origin, abb, desc FROM dictAbbs ORDER BY length(abb) DESC", *db);

    while (query.next())
        abbs[query.value(0).toString()] << AbbItem(query.value(1).toString(), query.value(2).toString());

    // teaser
    setHtml("<center><br><img src=':/rc/home.png'><h1>susvAgatam</h1></center>");

    setReadOnly(true);
}

void Card::resizeEvent(QResizeEvent* event)
{
    if (windowType()) // Qt::Widget == 0 -> Main Card
        config->cardSize = event->size();

    QTextEdit::resizeEvent(event);
}

void Card::article(QString word, QString search)
{
    setWindowTitle(word);

    QString txt = "<p class='header'>" + word + "</p>";

    QSqlQuery query("SELECT origin, hom, desc FROM dictEntries WHERE word MATCH '" + word + "' " +
                    config->originSuff + " ORDER BY origin, hom", *db);

    QMap<QString, QList<QStringList> > recs;

    while (query.next())
        recs[query.value(0).toString()] << query.value(2).toString().split("\n", QString::SkipEmptyParts);

    foreach (const QString& name, config->originKeys)
        if (recs[name].count())
            txt +=  buildRec(name, recs[name]);

    setHtml(txt);

    if (search.isEmpty())
        return;

    QRegExp rx;
    rx.setCaseSensitivity(Qt::CaseInsensitive);

    if (search.startsWith(":RX:"))
        rx.setPattern("(?:" + search.mid(4) + ")");
    else
        rx.setPattern("\\b(?:" + search.replace(QRegExp("\\s+"), "|") + ")\\b");

    QTextCursor cursor;

    QList<ExtraSelection> selections;

    QTextCharFormat format;
    //format.setForeground(Qt::black);
    format.setBackground(Qt::yellow);

    while (!(cursor = document()->find(rx, cursor, QTextDocument::FindCaseSensitively)).isNull()) {
        ExtraSelection selection;
        selection.format = format;
        selection.cursor = cursor;
        selections.append(selection);
    }

    if (selections.count()) {
        setExtraSelections(selections);

        cursor = selections[0].cursor;
        cursor.movePosition(QTextCursor::StartOfWord);
        setTextCursor(cursor);
        ensureCursorVisible();
    }
}

QString Card::buildRec(QString origin, QList<QStringList> desc)
{
    QString txt = "<p class='name'>" + origin + "</p>";

    if (desc.count() == 1)
        txt += buildList(desc[0]);
    else
        for (int i = 0; i < desc.count(); i++)
            txt += "<p class='count'>" + QString("%1").arg(i + 1) + "</p>" + buildList(desc[i]);

    for (int i = 0; i < abbs[origin].count(); i++)
          txt = txt.replace(abbs[origin][i].rx, "\\1<strong class='abbs' title='" +
                                                 abbs[origin][i].desc + "'>\\2</strong>\\3");
    return txt + "<br>";
}

QString Card::buildList(QStringList desc)
{
    QString txt;

    for (int i = 0; i < desc.count(); i++)
        txt += "<p class='item'><span class='bull'>•</span><code>   </code>" +
               desc[i].replace(QRegExp("([\\x0900-\\x097f]+)"), "<strong class='deva'>\\1</strong>") + "</p>";

    return txt;
}
