# TODO

A log of tasks to return to later, ordered by no particular priority.

## Honoring note off bytes

Notes are turned off in `boar` by passing a note on signal with zero velocity, as is acceptable by the MIDI standard. It should also look for explicit note off signals and handle them the same way.

## Assertions

Since the number of envs, voices, etc is now determined at compile time, add assertions that these values are within specific bounds.
