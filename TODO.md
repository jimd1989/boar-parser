# TODO

A log of tasks to return to later, ordered by no particular priority.

## Honoring MIDI channels

`boari` should have a command line flag to set the MIDI channel it outputs with its notes. It currently defaults to 0. `boar` should have a flag to set its listening channel. It is also hardcoded to 0. There should also be an option for `boar` to listen to all channels. `boar` should also be able to forward note events from non-matching channels, as they might be intended for another instance in the pipe.

## Honoring note off bytes

Notes are turned off in `boar` by passing a note on signal with zero velocity, as is acceptable by the MIDI standard. It should also look for explicit note off signals and handle them the same way.
