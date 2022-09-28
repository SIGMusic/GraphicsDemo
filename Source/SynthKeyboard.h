/*
  ==============================================================================

    SynthKeyboard.h
    Created: 28 Sep 2022 2:45:30am
    Author:  andrew

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "WavetableSynth.h"

//==============================================================================
/*
*/
class SynthKeyboard  : public juce::Component,
                       public juce::MidiKeyboardState::Listener,
                       public juce::AudioSource
{
public:
    SynthKeyboard()
    {
        // In your constructor, you should add any child components, and
        // initialise any special settings that your component needs.

    }

    ~SynthKeyboard() override
    {
    }

    virtual void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override {}

    virtual void releaseResources() override { /* Nothing */ }

    virtual void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override {}

    virtual void handleNoteOn(juce::MidiKeyboardState *source,
                              int midiChannel,
                              int midiNoteNumber,
                              float velocity) override {}

    virtual void handleNoteOff(juce::MidiKeyboardState *source,
                               int midiChannel,
                               int midiNoteNumber,
                               float velocity) override {}

    void paint (juce::Graphics& g) override { /* Nothing */ }

    void resized() override
    {
        // This method is where you should set the bounds of any child
        // components that your component contains..

    }

    static constexpr inline float midiToFreq(juce::uint8 midi_note)
    {
        return 440.0 * std::pow(2.0, (midi_note - 69) / 12.0);
    }
private:
    WavetableSynth wavetable_synth_;
    juce::MidiKeyboardState midi_keyboard_state_;
    std::unique_ptr<juce::MidiKeyboardComponent> midi_keyboard_;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthKeyboard)
};
