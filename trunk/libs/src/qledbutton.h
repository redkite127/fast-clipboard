#ifndef QLEDBUTTON_H
#define QLEDBUTTON_H
//
#include <QPushButton>
#include <QColor>
#include <QResizeEvent>
#include "qled.h"

//
class QLedButton : public QPushButton
{
	Q_OBJECT

public:
	QLedButton(QWidget *parent = 0, QColor c = Qt::red);
	QLedButton(const QString &text,QWidget *parent = 0, QColor c = Qt::red);
	//QLedButton(const QIcon &icon, const QString &text, QWidget *parent = 0)
	~QLedButton();
	
	bool ledValue() const;
	QColor ledColor() const;
	
public slots:
	void setLedValue(bool);
	void setLedColor(QColor);
	void toggleLedValue();
	
private:
	void init();
	void resizeEvent(QResizeEvent *event); 
	
	QLed *led;
};
#endif
