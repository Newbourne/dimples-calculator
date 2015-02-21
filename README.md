## Dimples Calculator
C++ / NodeJS addon for parsing and generating dynamic string algorithms and calculations.

### Cloud 9 - Workspace Setup and Requirements

#### Ubuntu 14 Server
- Boost Libraries (v1.55) `apt-get install libboost-dev-all`
- NPM Package Manager `apt-get install npm`
- Node Manager `npm install n -g` then `sudo n install latest`
- Node Addon Compiler `npm install node-gyp -g`
- Git `apt-get install git`


### Compile C++ Only
`make -f makefile`

Binary will be located in \bin

### Compile Addon
`cd node`

`node-gyp build`

### Execute Node Test
`node test.js`
