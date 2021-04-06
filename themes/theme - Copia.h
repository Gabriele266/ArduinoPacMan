/*
 * Rappresenta un tema in ArduinoPacMan
 * */

#ifndef THEME_H
#define THEME_H

#include <QString>
#include <QFile>
#include <QColor>
#include <QRgb>
#include <QDomAttr>
#include <QDomDocument>
#include <QDomElement>

#include "utils/utils.h"
#include "utils/macros.h"
#include "packages/nameditem.h"
#include "packages/attributeditem.h"
#include "threads/fileloader.h"

class Theme : public AttributedItem
{
public:
    Theme();

    GETTER_SETTERC(QString, file, ThemeFile,
                   Imposta il file da utilizzare per il tema,
                   Restituisce il file da utilizzare per il tema)

    /**
      Restituisce lo stylesheet del tema */
    GETTER(QString, style, styleSheetBuffer)

    /**
     * @brief loadTheme Avvia il caricamento del tema
     * @return
     */
    bool loadTheme();

private:
    // File del tema
    QString file;

    // Buffer dello stylesheet
    QString style;

    // Indica se il tema è stato caricato
    bool loaded = false;

    // Colore da utlizzare in caso di errori
    QColor error_color;
    // Colore da utlizzare in caso di successo
    QColor success_color;
    // Colore di default del testo normale
    QColor normal_text_color;
    // Colore normale delle descrizioni
    QColor descriptions_color;
    // Colore normale dello sfondo
    QColor normal_background_color;
    // Colore normale di evidenziazione
    QColor highlight_background_color;
    // Colore del testo evidenziato
    QColor highlight_text_color;
};

#endif // THEME_H
