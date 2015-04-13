// Declare this variable before loading RequireJS JavaScript library
// To config RequireJS after it’s loaded, pass the below object into require.config();

requirejs.config({
	paths : {	
		jquery : "node_modules/jquery/dist/cdn/jquery-2.1.3.min",
		bootstrap : "node_modules/bootstrap/dist/js/bootstrap.min",
		backbone: "node_modules/backbone/backbone-min",
		underscore : "node_modules/underscore/underscore-min",
		backbonemarionette : "node_modules/backbone.marionette/lib/backbone.marionette.min"
	},
    shim : {
        "bootstrap" : { "deps" :['jquery'] }
    }
});