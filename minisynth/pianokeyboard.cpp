#include "pianokeyboard.h"
#include "ui_pianokeyboard.h"

#include <QPushButton>

#include <utility>
#include <vector>

PianoKeyboard::PianoKeyboard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PianoKeyboard)
{
    ui->setupUi(this);

    const std::vector <std::pair <PianoKey, QPushButton *> > keyWidgets {
        std::pair (PianoKey::C, ui->btnC),
        std::pair (PianoKey::Csharp, ui->btnCs),
        std::pair (PianoKey::D, ui->btnD),
        std::pair (PianoKey::Dsharp, ui->btnDs),
        std::pair (PianoKey::E, ui->btnE),
        std::pair (PianoKey::F, ui->btnF),
        std::pair (PianoKey::Fsharp, ui->btnFs),
        std::pair (PianoKey::G, ui->btnG),
        std::pair (PianoKey::Gsharp, ui->btnGs),
        std::pair (PianoKey::H, ui->btnH),
        std::pair (PianoKey::Hsharp, ui->btnHs),
        std::pair (PianoKey::A, ui->btnA)
    };

    for (auto k : keyWidgets) {
        const PianoKey key = k.first;
        connect(k.second,
                &QPushButton::pressed,
                [this, key] () {
                    emit pressed(key);
                });
        connect(k.second,
                &QPushButton::released,
                [this, key] () {
                    emit released(key);
                });
    }
}

PianoKeyboard::~PianoKeyboard()
{
}
