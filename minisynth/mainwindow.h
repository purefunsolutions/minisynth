#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAudioDevice>
#include <QAudioFormat>
#include <QAudioSink>
#include <QMediaDevices>

#include <memory>

#include "circularbuffer.h"
#include "pianokeyboard.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_frequencySlider_valueChanged(int value);
    void on_bytesRead(qint64 pos, qint64 count);

private:
    std::unique_ptr <Ui::MainWindow> ui;
    QByteArray byteArray;
    CircularBuffer buffer;
    QAudioFormat audioFormat;
    QAudioDevice device;
    QAudioSink audio;
    PianoKeyboard piano;

    constexpr static const qreal sampleRate = 44100;
    qreal frequency = 440;

    quint64 phase = 0;
};
#endif // MAINWINDOW_H
