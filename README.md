# boar-parser

Experimental attempt at a better parser for [boar](https://github.com/jimd1989/boar). Do not use this yet.

## Motivation

1. Represent time-sensitive performance data, such as note on/off, as standard MIDI bytes. Avoid needless parsing.
2. Provide a greater level of flexibility and type safety in non time-critical control values.
3. Allow `boar` itself to become more complex: more operators, routings, envelopes, etc.

## Design

Once refactored, `boar` will act as a pure sound server that accepts binary messages of the form

```
[magic word (int)] [size (short)] [cmd (byte)] [vals (variable) ...]
```

This interpreter, `boari`, will take plaintext commands like `w1 sine`, and output them in the above binary format. These commands will ideally be able to interleave themselves with a standard MIDI stream of note on/off messages coming from an external source. 
