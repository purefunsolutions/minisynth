#ifndef PIANOKEYBOARD_H
#define PIANOKEYBOARD_H

#include <QWidget>

#include <memory>

#include "pianokeys.h"

namespace Ui {
class PianoKeyboard;
}

class PianoKeyboard : public QWidget
{
    Q_OBJECT

public:
    explicit PianoKeyboard(QWidget *parent = nullptr);
    ~PianoKeyboard();

signals:
    void pressed(PianoKey key);
    void released(PianoKey key);

private:
    std::unique_ptr<Ui::PianoKeyboard> ui;
};

#endif // PIANOKEYBOARD_H
