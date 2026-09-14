# ViBIT2

**vibit2** is a cross-platform command line teletext packet stream (T42) generator tool written in Python, which is a fork of [vbit2](https://github.com/peterkvt80/vbit2) made by Peter Kwan.

This fork expands upon original vbit2's source code with a number of new features that were planned by me and implemented **with the help of AI coding tools**. The project was basically created out of curiosity, to see if AI is now mature enough to understand some less known features of teletext and add them to existing teletext stream software. **If AI assisted coding is something that is bothering you, you don't have to use this tool.**

## Added features

The following is the list of new features in vibit2 compared to the original vbit2:

* **Serial magazine broadcast mode**: In comparison to parallel mode (the only supported in original vbit2) that divides VBI lines between magazines, serial mode transmits one complete magazine at a time sequentially. vibit2 supports both modes, and the currently used mode can be specified in the configuration file.
* **Reverse page broadcast**: When enabled in configuration file, the pages are broadcasted in the reverse order (from 899 to 100 instead of from 100 to 899).
* **Additional header row substitutions**: In addition to existing substitution templates, vibit2 adds possibility to display the _total number of subpages_ of a page, and _the number of currently transmitted subpage_ in the service header, with and without trailing zero. The day name can now also be displayed in two- or three-character format.
* **Localised day and month names**: The language of the day and month name displayed in the header can now be changed independently of the locale of the system that vbit2 runs on. 18 languages are supported, and the currently used one can be specified in configuration file.
* **Scrolling clock message**: If a clock is present in the header, it can be temporarily replaced every X seconds by a scrolling text message specified in the configuration file. Its appearance frequency and scrolling speed are also configurable.
* **Control codes in the status display**: The 20 character broadcast service data packet status message accepts 8-bit control codes and 7-bit TTI escape sequences in the same way as the header.

All features are verified and working correctly where tested. More new features might potentially be added in the future - I'm open to your ideas in this regard.

## Todo

- [x] Build and run on Windows
- [ ] Build and run on Linux
- [x] Verify that new features are working, both in a teletext stream player and on a real TV
- [x] Verify that none of existing features are broken
- [x] Test generating a T42 stream
- [x] Test piping a teletext stream into a dedicated player
- [ ] Test piping a teletext stream into raspi-teletext (I don't have a Raspberry Pi so I'd appreciate help in testing it if possible)
- [x] Test piping a teletext stream into hacktv
- [x] Review newly added code
- [ ] Cleanup of code and documentation
- [ ] Check if there could be any other new features to add (TOP Text support?)

## Building and running

Linux or Raspberry Pi OS:

    make -j4

Windows (MSYS2 UCRT64):

    make OS=Windows_NT -j4

Both produce a `vibit2` executable in the source directory. A `Dockerfile` is included for a container build.

Run it with the directory that holds the page files and the configuration:

    ./vibit2 --dir /path/to/service

The output can be piped in the command line into a file (in T42 format), an in-vision teletext stream player, or an another tool that outputs generated teletext signal to a compatible device, like [raspi-teletext](https://github.com/ali1234/raspi-teletext) or [hacktv](https://codeberg.org/fsphil/hacktv).

## AI use disclaimer

The features listed above were written by an AI coding agent working on the code with its
author, who specified, steered, tested and accepted the work. All changes were reviewed and
built by the human author.

* This code is provided as is, without warranty of any kind.
* AI generated code can be wrong or subtly non-compliant with the teletext standards (ETS 300 706 and related specifications). Behaviour was verified against the transmitted stream and on real hardware where possible, but not every path has been exercised on every receiver.
* Check the output on your own equipment, and keep your own backup of any service you
  broadcast, before relying on it.

## Acknowledgement

Thanks to Peter Kwan (peterkvt80) and other contributors for their excellent work on the following tools without which my project wouldn't have been possible:
- [vbit2](https://github.com/peterkvt80/vbit2)
- [vbit-iv](https://github.com/peterkvt80/vbit-iv)
- [vhs-teletext](https://github.com/ali1234/vhs-teletext)

Original readme for vbit2 follows below:

# VBIT2

An installation guide and more can be found in the [github wiki](https://github.com/peterkvt80/vbit2/wiki).

## About

This program takes a set of teletext [page files](https://github.com/peterkvt80/vbit2/wiki/Page-files) and generates a feature rich transmission stream on stdout or via a TCP server socket.

The transmission stream can be piped to raspi-teletext or any other application that needs a teletext packet stream.
It is a console application that can be compiled for Linux or Windows.

It generates a T42 teletext stream that can be piped to [raspi-teletext](https://github.com/ali1234/raspi-teletext) to add a teletext signal to the Raspberry Pi composite output, [vbit-py](https://github.com/peterkvt80/vbit-py) to drive a Vbit teletext inserter board, or into the [vbit-iv](https://github.com/peterkvt80/vbit-iv) in-vision renderer.

VBIT2 can also optionally generate output an mpeg transport stream containing DVB-TXT for merging into a digital television stream.

## Features

VBIT2 includes the following features:
* Parallel mode transmission of teletext magazines.
* Cycling subpage carousels.
* Level 1.5 and 2.5 features including dynamic character and object downloading pages and Packet 29 insertion.
* Format 1 Broadcast Service Data Packet generation with automatic daylight saving time adjustment.
* Fastext and TOP navigation support.
* IDL Format A and B data broadcast transmission.
* TCP control interface for live manipulation of teletext pages and service parameters.
* DVB-TXT packetized elementary stream generation.
* Network packet server to provide a teletext packet stream to multiple clients.
