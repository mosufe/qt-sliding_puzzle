#include "resources.h"

Pixmap::Pixmap(const QPixmap &pix) : QObject(), QGraphicsPixmapItem(pix)
{
    setCacheMode(DeviceCoordinateCache);
}
