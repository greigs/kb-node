global.$ = $;
var bower =  require('bower');
var inquirer =  require('inquirer');
var shell = require('nw.gui').Shell;

bower.commands
.install(['jquery'], { save: true }, { interactive: true })
// ..
.on('prompt', function (prompts, callback) {
    inquirer.prompt(prompts, callback);
});

var serialPort = require("serialport");


var content = $('.content');

$(document).ready(function() {
	serialPort.list(function (err, ports) {
	  ports.forEach(function(port) {
	    content.push(port.comName);
	    console.log(port.pnpId);
	    console.log(port.manufacturer);
	  });
	});
});