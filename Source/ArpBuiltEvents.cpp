//
// This file is part of LibreArp
//
// LibreArp is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// LibreArp is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see https://librearp.gitlab.io/license/.
//

#include "ArpBuiltEvents.h"

ArpBuiltEvents::PlayingNote::PlayingNote(int noteNumber, int outChannel) : noteNumber(noteNumber), outChannel(outChannel) {}

bool operator> (ArpBuiltEvents::PlayingNote const &a, ArpBuiltEvents::PlayingNote const &b) {
    return a.noteNumber > b.noteNumber;
}
bool operator< (ArpBuiltEvents::PlayingNote const &a, ArpBuiltEvents::PlayingNote const &b) {
    return a.noteNumber < b.noteNumber;
}
bool operator>=(ArpBuiltEvents::PlayingNote const &a, ArpBuiltEvents::PlayingNote const &b) {
    return a.noteNumber >= b.noteNumber;
}
bool operator<=(ArpBuiltEvents::PlayingNote const &a, ArpBuiltEvents::PlayingNote const &b) {
    return a.noteNumber <= b.noteNumber;
}
bool operator==(ArpBuiltEvents::PlayingNote const &a, ArpBuiltEvents::PlayingNote const &b) {
    return a.noteNumber == b.noteNumber && a.outChannel == b.outChannel;
}

ArpBuiltEvents::EventNoteData ArpBuiltEvents::EventNoteData::of(NoteData &orig, unsigned long noteIndex) {
    EventNoteData result;
    result.noteNumber = orig.noteNumber;
    result.velocity = orig.velocity;
    result.pan = orig.pan;
    result.noteIndex = noteIndex;

    return result;
}
