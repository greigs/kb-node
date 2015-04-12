global.$ = $;
var bower =  require('bower');
var inquirer =  require('inquirer');
//var shell = require('nw.gui').Shell;
require('nw.gui').Window.get().showDevTools()

bower.commands
.install(['jquery'], { save: true }, { interactive: true })
// ..
.on('prompt', function (prompts, callback) {
    inquirer.prompt(prompts, callback);
});

var SerialPort = require("serialport").SerialPort;
var serialPort = null;


var content = $('.content');

function openSerial(comPort){
	
	if (serialPort !== null){
		serialPort.close();
	}
	serialPort = new SerialPort(comPort, {
	  baudrate: 115200
	});

	serialPort.on("open", function () {
	  console.log('open');
	  serialPort.on('data', function(data) {
	    console.log('data received: ' + data);
	    //serialPort.close();
	  });

	/*
	  serialPort.write("%da\n");
	  serialPort.write("%ua\n");
	  serialPort.write("%db\n");
	  serialPort.write("%ub\n");
	  serialPort.write("%dc\n");
	  serialPort.write("%uc\n");
	*/

	});

	return serialPort;
}

$(function() {

var serialPort = require("serialport");

	var arduinoCom = null;
	serialPort.list(function (err, ports) {
	  ports.forEach(function(port) {
	    console.log(port.comName);
	    console.log(port.pnpId);
	    console.log(port.manufacturer);
	    if (port.manufacturer === 'Arduino LLC (www.arduino.cc)'){
	    	arduinoCom = port.comName;
	    }
	  });
	  var serial = openSerial(arduinoCom);
	});

});