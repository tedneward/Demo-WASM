const util = require('util');
const fs = require('fs');

var srcFile = process.argv[2]; 
var source = fs.readFileSync(srcFile);

// {{## BEGIN setup ##}}
const env = {
    memoryBase: 0,
    tableBase: 0,
    memory: new WebAssembly.Memory({
        initial: 256
    }),
    table: new WebAssembly.Table({
        initial:0,
        element:'anyfunc'
    }),
}
var typedArray = new Uint8Array(source);
var importObject = {
    env: env,
    // imported functions go here
    imports: {
        imported_func: arg => console.log(arg)
    }
};// {{## END setup ##}}

// {{## BEGIN instantiate ##}}
WebAssembly.instantiate(typedArray, importObject)
.then(result => {
    console.log(util.inspect(result, true, 0));
    let module = result.module;
    let instance = result.instance;
    console.log(util.inspect(instance, true, 0));
    let exports = instance.exports;
    console.log(util.inspect(exports, true, 0));
    let add = exports.add;
    console.log(add(2, 2));
    exports.calli();
}).catch(e => {
    console.log("ERROR: " + e);
});
// {{## END instantiate ##}}

