#ifndef QLINEEDITESSE_H
#define QLINEEDITESSE_H

#include <QLineEdit>
#include <QMouseEvent>

/***
 *  Select all the text of the QLineEdit when the widget is clicked
 *
 */

class QLineEditEsse : public QLineEdit
{
    Q_OBJECT

public:
    QLineEditEsse ( QWidget * parent = 0 );
    QLineEditEsse ( const QString & contents, QWidget * parent = 0 );
    ~QLineEditEsse();


protected:
    void mousePressEvent(QMouseEvent *);
};

#endif
