#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QtMath>

static QAudioFormat getAudioFormat(qreal sampleRate)
{
    // Set QAudioFormat parameteres
    QAudioFormat audioFormat;
    audioFormat.setSampleRate(static_cast<int>(sampleRate));
    audioFormat.setChannelCount(1);
    audioFormat.setSampleFormat(QAudioFormat::Float);

    return audioFormat;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , byteArray(8192*4, 0)
    , buffer(&byteArray, nullptr)
    , audioFormat(getAudioFormat(sampleRate))
    , device(QMediaDevices::defaultAudioOutput())
    , audio(device, audioFormat)
    , piano(nullptr)
{
    ui->setupUi(this);

    ui->verticalLayout->addWidget(&piano);

    buffer.open(QIODevice::ReadWrite);

    // Verify the raw audio format is supported by the device
    if(!device.isFormatSupported(audioFormat))
    {
        qWarning() <<
            "Raw audio format not supported by backend, cannot play audio.";
        return;
    }

    // In case the circular buffer is not filled fast enough, connect this
    // signal
    connect(&audio, &QAudioSink::stateChanged, [this](QAudio::State newState)
    {
        if (newState == QAudio::IdleState)
        {
            // No more data in the buffer
            qDebug() << "QAudioSink entered IdleState";
        }
    });

    connect(&buffer,
            &CircularBuffer::bytesRead,
            this,
            &MainWindow::on_bytesRead);

    connect(&piano,
            &PianoKeyboard::pressed,
            this,
            &MainWindow::pianokey_pressed);

    connect(&piano,
            &PianoKeyboard::released,
            this,
            &MainWindow::pianokey_released);

    audio.start(&buffer);
}

MainWindow::~MainWindow()
{
}

void MainWindow::on_frequencySlider_valueChanged(int value)
{
    frequency = static_cast<qreal> (value);
    qDebug() << "Frequency set to: " << frequency << " Hz";
}

void MainWindow::on_bytesRead(qint64 pos, qint64 count)
{
    for (quint32 i = pos / 4; i < (pos + count) / 4; i++)
    {
        qreal sinVal = (qreal)qSin(2.0 * M_PI * frequency * phase / sampleRate);
        ++phase;

        float sample = (float)sinVal;

        char *ptr = (char*)(&sample);
        char byte00 = *ptr;
        char byte01 = *(ptr + 1);
        char byte02 = *(ptr + 2);
        char byte03 = *(ptr + 3);

        byteArray[4 * i] = byte00;
        byteArray[4 * i + 1] = byte01;
        byteArray[4 * i + 2] = byte02;
        byteArray[4 * i + 3] = byte03;
    }
}

void MainWindow::pianokey_pressed(PianoKey key)
{
    qDebug() << "PianoKey pressed: " << key;

    const qreal baseOctave = 48.0;
    const qreal keyReal = static_cast <qreal> (key);
    frequency = 440.0 * qPow(2, ((baseOctave + keyReal) - 49) / 12);
}

void MainWindow::pianokey_released(PianoKey key)
{
    qDebug() << "PianoKey released: " << key;
}
