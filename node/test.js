var addon = require('./build/Release/addon');

var obj = new addon.Wrapper();

var obj2 = obj.solve('1+2');

console.log('Problem: ' + obj2.problem + ' - Answer: ' + obj2.solution);
