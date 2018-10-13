#include "toggleswitch.h"

ToggleSwitch::ToggleSwitch(QWidget *parent) :
    QAbstractButton(parent),
    m_status(false),
    m_margin(3),
    m_bodyBrush(QColor(223, 136, 86))
{
    this->setBrush(QColor(223, 136, 86));
}

void ToggleSwitch::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);
    painter.setPen(Qt::NoPen);

    if(this->isEnabled())
    {
        painter.setBrush(this->m_status ? this->brush(): Qt::gray);
        painter.setOpacity(0.8);
        painter.setRenderHint(QPainter::Antialiasing, true);

        painter.drawRoundedRect(QRect(this->m_margin, this->m_margin, this->width() - 2 * this->m_margin,
            this->height() - 2 * this->m_margin), 18.0, 18.0);

        painter.setBrush(this->m_bodyBrush);
        painter.setOpacity(1.0);

        if(!this->m_status)
        {
            painter.drawEllipse(QRectF(this->width() - this->height(), static_cast<int>((this->height() / 2) - (this->height() / 2)),
              this->height(), this->height()));
        }
        else
        {
            painter.drawEllipse(QRectF(0, static_cast<int>((this->height() / 2) - (this->height() / 2)),
              this->height(), this->height()));
        }
    }
    else
    {
        painter.setBrush(QColor(213, 126, 76));
        painter.setOpacity(1.0);

        painter.drawRoundedRect(QRect(this->m_margin, this->m_margin, this->width() - 2 * this->m_margin,
            this->height() - 2 * this->m_margin), 18.0, 18.0);

        painter.setOpacity(0.3);
        painter.setBrush(QColor(213, 126, 76));

        painter.drawEllipse(QRectF(static_cast<int>(this->width() / 2), static_cast<int>((this->height()/2) - (this->height()/2)),
            this->height(), this->height()));
    }

    event->setAccepted(true);
}

void ToggleSwitch::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() & Qt::LeftButton)
    {
        this->m_status = !this->m_status;
        emit ToggleSwitch::statusChanged(this->m_status);
    }

    QAbstractButton::mouseReleaseEvent(event);
}

QSize ToggleSwitch::sizeHint() const
{
    return {this->width() + (2 * this->m_margin), this->height() + (2 * this->m_margin)};
}
