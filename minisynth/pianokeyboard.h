#ifndef PIANOKEYBOARD_H
#define PIANOKEYBOARD_H

#include <QWidget>

#include <memory>

namespace Ui {
class PianoKeyboard;
}

class PianoKeyboard : public QWidget
{
    Q_OBJECT

public:
    explicit PianoKeyboard(QWidget *parent = nullptr);
    ~PianoKeyboard();

private:
    std::unique_ptr<Ui::PianoKeyboard> ui;
};

#endif // PIANOKEYBOARD_H
