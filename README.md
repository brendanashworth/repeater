# repeater

Totally simple tool to repeat a command over..and over..and over until you fail to get a specified return code. Useful for looking for failing tests.

## Usage
```sh
$ ./repeater

Usage: repeater {command} [-h] [-d delay] [-m max] [-c code]
Flags:
  -h, --help     View this help
  -d, --delay n  Set delay between runs (ms), default 10
  -m, --max n    Set maximum number of runs, default 1000
  -c, --code n   Set needed code to continue, default 0

``

## License
[MIT](./LICENSE)