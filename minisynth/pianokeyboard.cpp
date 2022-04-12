#include "pianokeyboard.h"
#include "ui_pianokeyboard.h"

PianoKeyboard::PianoKeyboard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PianoKeyboard)
{
    ui->setupUi(this);
}

PianoKeyboard::~PianoKeyboard()
{
}
