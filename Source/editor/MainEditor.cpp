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

#include <sstream>
#include "../LibreArp.h"
#include "MainEditor.h"
#include "../exception/ArpIntegrityException.h"


const int RESIZER_SIZE = 18;

MainEditor::MainEditor(LibreArp &p, EditorState &e)
        : AudioProcessorEditor(&p),
          processor(p),
          state(e),
          resizer(this, &boundsConstrainer),
          tabs(TabbedButtonBar::Orientation::TabsAtTop),
          patternEditor(p, e),
          behaviourSettingsEditor(p),
          xmlEditor(p) {

    LookAndFeel::setDefaultLookAndFeel(&LArpLookAndFeel::getInstance());

    setSize(state.width, state.height);

    boundsConstrainer.setMinimumSize(200, 200);

    placeholderLabel.setText("Unimplemented component", NotificationType::dontSendNotification);
    placeholderLabel.setJustificationType(Justification::centred);
    placeholderLabel.setFont(Font(32.0f));
    placeholderLabel.setColour(Label::textColourId, Colour(255, 0, 0));

    tabs.setOutline(0);
    tabs.addTab("Pattern Editor",
            getLookAndFeel().findColour(ResizableWindow::backgroundColourId), &patternEditor, false);
    tabs.addTab("Behaviour",
            getLookAndFeel().findColour(ResizableWindow::backgroundColourId), &behaviourSettingsEditor, false);
    tabs.addTab("Global settings",
            getLookAndFeel().findColour(ResizableWindow::backgroundColourId), &placeholderLabel, false);
#if JUCE_DEBUG
    tabs.addTab("XML viewer",
            getLookAndFeel().findColour(ResizableWindow::backgroundColourId), &xmlEditor, false);
#endif
    tabs.addTab("About",
            getLookAndFeel().findColour(ResizableWindow::backgroundColourId), &aboutBox, false);

    addAndMakeVisible(tabs);
    addAndMakeVisible(resizer, 9999);
}

MainEditor::~MainEditor() = default;

//==============================================================================
void MainEditor::paint(Graphics &g) {
    g.setColour(LArpLookAndFeel::MAIN_BACKGROUND_COLOUR);
    g.fillRect(getLocalBounds());
}

void MainEditor::resized() {
    state.width = getWidth();
    state.height = getHeight();

    tabs.setBounds(getLocalBounds().reduced(8));
    resizer.setBounds(getWidth() - RESIZER_SIZE, getHeight() - RESIZER_SIZE, RESIZER_SIZE, RESIZER_SIZE);
}

void MainEditor::audioUpdate(uint32 type) {
    patternEditor.audioUpdate(type);
    xmlEditor.audioUpdate(type);
}
