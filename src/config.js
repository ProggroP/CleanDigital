Pebble.addEventListener('showConfiguration', function (e) {
	Pebble.openURL('http://chaoticweg.github.io/PebbleCleanFace/config.html');
});

Pebble.addEventListener('webviewclosed', function (e) {
	var config = JSON.parse(decodeURIComponent(e.response));
	
	Pebble.sendAppMessage({ 0 : config.draw_invert.toString() },
		function (e) {}, function (e) { console.log('error sending message: %s', e.error.message); });
});