# STraining
## Description
App designed to simplify(for me) training process(and taking food)

## Installation
Now only support linux(particulary [arch linux x64](https://www.archlinux.org/) with DE [KDE](https://kde.org/)) but you can try install on other platforms(such as Windows or MacOS)
### Linux
First you should install an open source version of [Qt](https://www.qt.io/download) 5.14.1 or greater(with GPLv3 license) and then run this commands:
```sh
$ git clone https://github.com/sakost/straining.git
$ qmake
$ make && make check
```
To install app into `/opt/` run with root:
```sh
# make install
```
And run by `/opt/straining/bin/`
### Windows
Try to install MinGW and [Qt](https://www.qt.io/download) 5.14.1 or greater(with GPLv3 license) toolkit and then run from command line with Administrator rights(using mingw make utility or another alternative):
> Warning: I haven't checked this code
```sh
$ qmake
$ mingw64-make && mingw64-make check
$ mingw64-make install
```

## Todo
* make more strict complex interface

## License
GNU GPL v3.0

