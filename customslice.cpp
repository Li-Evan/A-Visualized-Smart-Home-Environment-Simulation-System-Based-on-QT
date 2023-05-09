#include "customslice.h"

QT_CHARTS_USE_NAMESPACE

CustomSlice::CustomSlice(QString label, qreal value)
    : QPieSlice(label, value)
{
    connect(this, SIGNAL(hovered(bool)), this, SLOT(showHighlight(bool)));
}

QBrush CustomSlice::originalBrush()
{
    return m_originalBrush;
}

void CustomSlice::showHighlight(bool show)
{
    if (show) {
        QBrush brush = this->brush();
        m_originalBrush = brush;
        brush.setColor(brush.color().lighter());
        setBrush(brush);
    } else {
        setBrush(m_originalBrush);
    }
}

#include "moc_customslice.cpp"
