## Dimples Calculator
C++ / NodeJS addon for parsing and generating dynamic string algorithms and calculations.

Development: Active 

Start Date: Winter 2014

### Cloud 9 - Ubuntu 14 Server - Workspace
- Setup Cloud 9 provided SSH key (/.ssh/authorized_keys)
- Install NVM and latest version of Node.JS
- Boost Libraries (v1.55) `apt-get install libboost-all-dev`
- NPM Package Manager `apt-get install npm` 
- Update NPM `npm update`
- Node Addon Compiler `npm install node-gyp -g`
- Git `apt-get install git`

#### Compile C++ Only
`make -f makefile`

Binary will be located in \bin

#### Compile Addon
`cd node`

(run once) `node-gyp configure`

`node-gyp build`

#### Execute Node Test
`node test.js`
