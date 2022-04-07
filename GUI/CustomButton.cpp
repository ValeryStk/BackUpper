#include "CustomButton.h"
#include <qdebug.h>
const int height_scaled = 48;
const int width_scaled = 48;

CustomButton::CustomButton(QWidget* parent)
{
    this->setParent(parent);
    setPixmap(QPixmap(40,40));
}

void CustomButton::setPixmap(const QPixmap &pixmap)
{
     m_pixmap = pixmap.scaled(height_scaled,width_scaled);
}

void CustomButton::paintEvent(QPaintEvent *e)
{

    const QString textTemp = this->text();
    setText("");
    QPushButton::paintEvent(e);
    setText(textTemp);
    if (!m_pixmap.isNull()) {
      const int y = (height() - m_pixmap.height()) / 2;
      QPainter painter(this);

      if(isChecked()){
          painter.save();
          painter.setPen(Qt::NoPen);
          painter.setBrush(QBrush(QColor(240,240,240,255)));
          painter.drawRect(this->rect());
          painter.restore();
      }

      painter.drawPixmap(5, y, m_pixmap);
      painter.drawText(60,38,text());

      if(isChecked()){
          QPen pen;
          pen.setColor(QColor(69,199,249,255));
          pen.setWidth(3);
          painter.setPen(pen);
          painter.drawLine(m_pixmap.width()+12,this->height()-2,this->width()-2,this->height()-2);

      }

    }

}
