#include "circularbuffer.h"
#include <QDebug>

CircularBuffer::CircularBuffer(QByteArray *byteArray,
                               QObject *parent)
    : QBuffer(byteArray, parent)
{
}

CircularBuffer::~CircularBuffer()
{
}

qint64 CircularBuffer::readData(char *data, qint64 len)
{
    const qint64 startpos = pos();
    const qint64 count = QBuffer::readData(data, len);

    emit bytesRead(startpos, count);

    if (atEnd()) {
        seek(0);
    }

    return count;
}
