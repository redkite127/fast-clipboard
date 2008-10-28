#include "qledbutton.h"
//
QLedButton::QLedButton(QWidget *parent, QColor c) : QPushButton(parent)
{
	init();
	led->setColor(c);
};

QLedButton::QLedButton(const QString &text, QWidget *parent, QColor c) : QPushButton(text, parent)
{
	init();
	led->setColor(c);
};

QLedButton::~QLedButton()
{
	
};

bool QLedButton::ledValue() const
{
	return led->value();
};

QColor QLedButton::ledColor() const
{
	return led->color();
};

void QLedButton::setLedValue(bool v)
{
	led->setValue(v);
	return;
};

void QLedButton::setLedColor(QColor c)
{
	led->setColor(c);
	return;
};

void QLedButton::toggleLedValue()
{
	led->toggleValue();
	return;
};

void QLedButton::init()
{
	led = new QLed(this);
};

void QLedButton::resizeEvent(QResizeEvent *event)
{
	if(height() > width())
		led->resize(width(),width());
	else
		led->resize(height(),height());
	
	setStyleSheet(QString("QPushButton{ padding-left: %1; text-align: right; padding-right: 8; }").arg(led->width() * 0.8));
	
	event->accept();
};
//
