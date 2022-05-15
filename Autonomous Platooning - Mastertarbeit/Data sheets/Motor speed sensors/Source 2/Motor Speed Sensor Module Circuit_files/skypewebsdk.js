/* globals loadSkypeWebSdkAsync */
(function () {
    'use strict';

    var params = {
        scriptToLoad: 'https://swx.cdn.skype.com/shared/v/1.2.5/SkypeBootstrap.min.js',
        id: 'skype_bootstrap',
        callback: function callback() {
            window.Skype.initialize({ apiKey: 'shareButton' }, function () {}, function () {});
        }
    };

    loadSkypeWebSdkAsync(params);
})();
