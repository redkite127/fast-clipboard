#include "QLineEditEsse.h"

QLineEditEsse::QLineEditEsse ( QWidget * parent ) : QLineEdit( parent )
{
}

QLineEditEsse::QLineEditEsse ( const QString & contents, QWidget * parent ) : QLineEdit ( contents, parent )
{
}

QLineEditEsse::~QLineEditEsse ()
{
}

/***
 *   Simulate a DoubleClick to select all the text() or selectAll() ?
 *   Note : The widgets gets a mousePressEvent() and a mouseReleaseEvent() before the mouseDoubleClickEvent()
 */
void QLineEditEsse::mousePressEvent(QMouseEvent *e)
{
    //QLineEdit::mouseDoubleClickEvent(e);
    selectAll();
}
