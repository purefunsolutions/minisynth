#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H

#include <QBuffer>
#include <QByteArray>

class CircularBuffer : public QBuffer
{
    Q_OBJECT

public:
    CircularBuffer(QByteArray *byteArray, QObject *parent = nullptr);
    virtual ~CircularBuffer();

signals:
    void bytesRead(qint64 pos, qint64 bytes);

protected:
    virtual qint64 readData(char *data, qint64 len) override;

private:
};
#endif // CIRCULARBUFFER_H
