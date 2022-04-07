#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H
#include "QPushButton"
#include "QPainter"

class CustomButton:public QPushButton
{
public:
  explicit CustomButton(QWidget* parent = nullptr);
  virtual ~CustomButton() {}

  void setPixmap(const QPixmap& pixmap);

  virtual QSize sizeHint() const override {
    const auto parentHint = QPushButton::sizeHint();
    return QSize(parentHint.width() + m_pixmap.width(), std::max(parentHint.height(), m_pixmap.height()));
  }

protected:
  virtual void paintEvent(QPaintEvent* e) override;

private:
  QPixmap m_pixmap;
};

#endif // CUSTOMBUTTON_H
