function Startposition(map){
    var setByIpRequestID;
    this.geolocationError = function(g) {
        if ((g.code >= 0) && (g.code <= 3)) {
            this.setPositionByIp();
        }
        return true;
    };
    
    this.setGeolocatedPosition = function(i) {
	window.clearTimeout(setByIpRequestID); // got address, no need to ask
    	if(this.changed()){
    		return false;
    	}
        var h = new OpenLayers.LonLat(i.coords.longitude, i.coords.latitude);
        h = h.transform(epsg4326, this.map.getProjectionObject());
        var g = i.coords.accuracy / 2;
        var j = new OpenLayers.Bounds(h.lon - g, h.lat - g, h.lon + g, h.lat + g);
        this.map.zoomToExtent(j, true);
    };
    this.setPositionByIp = function() {
        var g = this;
        var h = OpenLayers.Request.GET({
            url : "/location.php",
            async : true,
            success : function(j) {
            	if(g.changed()){
            		return false;
            	}
                var i = j.responseText;
                if ((i.length > 0) && (i != "NULL")) {
                    i = i.split("|");
                    var l = new OpenLayers.LonLat(i[5], i[4]);
                    l = l.transform(epsg4326, g.map.getProjectionObject());
		    g.map.setCenter(l, 10);
                    return true;
                } else {
                    return false;
                }
            }
        });
    };
    this.changed = function(){
    	if(this.map.getZoom() != this.zoom){
    		return true;
    	}
    	return false;
    };
    
    this.map = map;
    this.center = this.map.getCenter();
    this.zoom = this.map.getZoom();
    var t = this;

    // FF do not call failure callback if user refuses to provide Geo Location.
    // Therefore we prepare call for setLocationByIP after some time
    setByIpRequestID = window.setTimeout(
	function(){
	    t.setPositionByIp();
	}, 5000 /* 5 secs */);

    if ((navigator.geolocation) && (typeof navigator.geolocation.getCurrentPosition != "undefined")) {
        var a = this;
        navigator.geolocation.getCurrentPosition(function(g){a.setGeolocatedPosition(g);}, function(g){a.geolocationError(g);});
    } else {
        this.setPositionByIp();
    }
};
