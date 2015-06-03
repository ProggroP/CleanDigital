// var config_url = 'http://127.0.0.1:52120/config.html?v=1.3'; // for testing using Brackets

var config_url = 'http://chaoticweg.github.io/PebbleCleanFace/config.html?v=1.3';

Pebble.addEventListener('showConfiguration', function (e) {
	var url    = config_url;
	
	for (var i = 0; i < localStorage.length; i++) {
		var key   = localStorage.key(i);
		var value = localStorage.getItem(key);
		
		if (value !== null)
			url += '&' + encodeURIComponent(key) + '=' + encodeURIComponent(value);
	}
	
	Pebble.openURL(url);
});

Pebble.addEventListener('webviewclosed', function (e) {
	if (!e.response)
		return;
	
	var values = JSON.parse(decodeURIComponent(e.response));
	
	for (var key in values) {
		values[key] = values[key].toString();
		localStorage.setItem(key, values[key]);
	}
	
	Pebble.sendAppMessage(values,
		function(e) { console.log('sent config to Pebble'); },
		function(e) { console.log('sending config failed: ', e.error.message); });
});