var current_version = '1.5';

var config_url = {
	legacy : 'http://chaoticweg.github.io/PebbleCleanFace/config.html?v=' + current_version,
	aplite : 'http://chaoticweg.github.io/PebbleCleanFace/config-aplite.html?v=' + current_version,
	basalt : 'http://chaoticweg.github.io/PebbleCleanFace/config-basalt.html?v=' + current_version
};

function getPlatform() {
	if (Pebble.getActiveWatchInfo)
		return Pebble.getActiveWatchInfo().platform;

	return 'legacy';
}

Pebble.addEventListener('ready', function (e) {
	console.log('running pebblekit.js for ' + getPlatform());
});

Pebble.addEventListener('showConfiguration', function (e) {
	var platform    = getPlatform();

	var not_the_url = config_url[platform];
	console.log('when updated, we will be showing the following URL:');
	console.log(not_the_url);

	var url    = config_url.legacy;
	console.log('instead we are showing:');
	console.log(url);

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
