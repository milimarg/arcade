# Welcome to the Arcade Project

The Arcade Project's goal is to create a Core program that can run given graphics libraries and games using .so files. \
Games and graphics libraries can be changed at runtime.

The Core program must handle basic features, like an events wrapper or a pixels wrapper.

## Installation

```shell
git clone https://github.com/EpitechPromo2027/B-OOP-400-STG-4-1-arcade-noe.tritsch
```

## Build

### Whole project

```shell
make
```

### Only Core program

```shell
make -C core
```

### Only games

```shell
make -C games
```

### Only graphics libraries

```shell
make -C graphics
```

### Only a given library

```shell
make -C <filepath to lib> # i.e. './lib/SDL2' or './lib/Pacman'
```

## Run

```shell
./arcade <filepath to graphics lib> # i.e './lib/arcade_sdl2.so'
```

## Documentation

- [Add a new game](./doc/ADD-NEW-GAME.md)
- [Add a new graphics library](./doc/ADD-NEW-GRAPHICS.md)
- [Class hierarchy](https://flguitt.com/arcade)
- [Game controls](./doc/GAME-CONTROLS.md)

## Credits

[Augustin GROSNON](https://github.com/augustin-grosnon) \
[Noé TRITSCH](https://github.com/NeonMagique) \
[Florent GUITTRE](https://github.com/milimarg)
