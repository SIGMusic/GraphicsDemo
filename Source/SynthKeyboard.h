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
        // Allowed since we derive from MidiKeyboardState::Listener
        midi_keyboard_state_.addListener(this);

        // Free previous pointer and instantiate (reduces likelihood of memory leak)
        midi_keyboard_.reset(new juce::MidiKeyboardComponent(midi_keyboard_state_,
                 juce::KeyboardComponentBase::Orientation::horizontalKeyboard));
        addAndMakeVisible(midi_keyboard_.get());
    }

    ~SynthKeyboard() override
    {
    }

    virtual void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override
    {
        wavetable_synth_.prepareToPlay(samplesPerBlockExpected, sampleRate);
    }

    virtual void releaseResources() override { /* Nothing */ }

    virtual void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override
    {
        wavetable_synth_.getNextAudioBlock(bufferToFill);
    }

    virtual void handleNoteOn(juce::MidiKeyboardState *source,
                              int midiChannel,
                              int midiNoteNumber,
                              float velocity) override
    {
        wavetable_synth_.setFrequency(midiToFreq((juce::uint8) midiNoteNumber));
        wavetable_synth_.setAmplitude(0.5);
    }

    virtual void handleNoteOff(juce::MidiKeyboardState *source,
                               int midiChannel,
                               int midiNoteNumber,
                               float velocity) override
    {
        wavetable_synth_.setAmplitude(0.0);
    }

    void paint (juce::Graphics& g) override { /* Nothing */ }

    void resized() override
    {
        // Fill this component with the keyboard
        midi_keyboard_->setBounds(getLocalBounds());
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
