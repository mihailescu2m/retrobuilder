# retrobuilder

Collection of scripts for compiling and installing retro emulators.
It consists of the main "setup" script, and the emulators "inc" scripts that define compilation and configuration options.
Sources are from git repositories, with patches added for the Odroid C1 (fbdev) platform.

Example usage:

* Compiling and installing retroarch from git repository:
  ./setup retroarch.inc

* Getting retroarch sources from repository:
  ./setup retroarch.inc fetch

* Building retroarch from sources:
  ./setup retroarch.inc build

Contributions are welcomed.
