#ifndef CEBITOR_H
#define CEBITOR_H

#include "QsciLexerGlsl.h"

#include <Qsci/qsciscintilla.h>
#include <QEvent>
#include <QWidget>

//------------------------------------------------------------------------------------------------------------------------
/// @file Cebitor.h
/// @brief CEB text editor, implementation of QScintilla
/// @author Phil Rouse
/// @version 1.0
/// @date 03/03/16
//------------------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------------------
/// @class Cebitor
/// @brief CEB text editor class derived from QsciScintilla
//------------------------------------------------------------------------------------------------------------------------
class Cebitor : public QsciScintilla
{
  Q_OBJECT;

public:
  //------------------------------------------------------------------------------------------------------------------------
  /// @brief Cebitor constructor, initialises default values
  //------------------------------------------------------------------------------------------------------------------------
  Cebitor(QWidget *_parent);
protected slots:
  void comment();
};

#endif
