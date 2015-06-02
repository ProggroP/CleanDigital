Pebble.addEventListener('showConfiguration', function (e) {
	Pebble.openURL('http://chaoticweg.github.io/PebbleCleanFace/config.html');
});

Pebble.addEventListener('webviewclosed', function (e) {
	var response	= JSON.parse(decodeURIComponent(e.response));
	var action		= response.action;
	
	// if user cancelled without an action
	if (!action)
		return;
	
	Pebble.sendAppMessage({ CONFIG_ACTION : action.toString() },
		function (e) {}, function (e) { console.log('error sending message: %s', e.error.message); });
});