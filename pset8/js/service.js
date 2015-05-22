/**
 * service.js
 *
 * Computer Science 50
 * Problem Set 8
 *
 * Implements a shuttle service.
 */

// default height
var HEIGHT = 0.8;

// default latitude
var LATITUDE = 42.3745615030193;

// default longitude
var LONGITUDE = -71.11803936751632;

// default heading
var HEADING = 1.757197490907891;

// default number of seats
var SEATS = 10;

// default velocity
var VELOCITY = 50;

// global reference to shuttle's marker on 2D map
var bus = null;

// global reference to 3D Earth
var earth = null;

// global reference to 2D map
var map = null;

// global reference to shuttle
var shuttle = null;

// global points
var POINTS = 0;

// load version 1 of the Google Earth API
google.load("earth", "1");

// load version 3 of the Google Maps API
google.load("maps", "3", {other_params: "sensor=false"});

// once the window has loaded
$(window).load(function() {

    // listen for keydown anywhere in body
    $(document.body).keydown(function(event) {
        return keystroke(event, true);
    });

    // listen for keyup anywhere in body
    $(document.body).keyup(function(event) {
        return keystroke(event, false);
    });

    // listen for click on Drop Off button
    $("#dropoff").click(function(event) {
        dropoff();
    });

    // listen for click on Pick Up button
    $("#pickup").click(function(event) {
        pickup();
    });

    // load application
    load();
});

// unload application
$(window).unload(function() {
    unload();
});

/**
 * Renders seating chart.
 */
function chart()
{
    // sort seats
    shuttle.seats.sort(sortseats);
    
    var html = "<ol start='0'>";
    for (var i = 0; i < shuttle.seats.length; i++)
    {
        if (shuttle.seats[i] == null)
        {
            html += "<li>Empty Seat</li>";
        }
        else
        {
            html += "<li>" + 'To: ' + shuttle.seats[i].house + ' - ' + shuttle.seats[i].name + "</li>";
        }
    }
    html += "</ol>";
    $("#chart").html(html);
}

/**
 * Drops up passengers if their stop is nearby.
 */
function dropoff()
{
    // variable to store if shuttle is near any houses
    var house_counter = 0;
    
    // variable to count how many drop offs
    var dropoff_counter = 0;
    
    // loop through houses and see if user is close to any
    for (var house in HOUSES)
    {
        // get coordinates of the house
        var lat = HOUSES[house].lat
        var lng = HOUSES[house].lng;
        
        // calculate the distance from the current position of shuttle
        var d = shuttle.distance(lat, lng);
        
        // check if any houses are nearby
        if (d <= 30)
        {
            house_counter += 1;
            
            var drop_house = house;
            
            for (var i in shuttle.seats)
            {
                if (shuttle.seats[i] == null)
                {
                    // skip
                    continue;
                }
                if (shuttle.seats[i].house == drop_house)
                {
                    shuttle.seats[i] = null;
                    chart();
                    SEATS += 1;
                    // give user a point
                    POINTS += 1;
                    // update score on interface
                    $("#announcements").html("You made a dropoff!   -   Current Score: " + POINTS);
                    // increment dropoff counter
                    dropoff_counter += 1;
                }
            }
        }  
    }
    
    if (house_counter === 0)
    {
        $("#announcements").html("No houses are nearby!   -   Current Score: " + POINTS);
    }
    else if (house_counter > 0 && dropoff_counter === 0)
    {
        $("#announcements").html("No passengers live here!   -   Current Score: " + POINTS);
    }
}

/**
 * Called if Google Earth fails to load.
 */
function failureCB(errorCode) 
{
    // report error unless plugin simply isn't installed
    if (errorCode != ERR_CREATE_PLUGIN)
    {
        alert(errorCode);
    }
}

/**
 * Handler for Earth's frameend event.
 */
function frameend() 
{
    shuttle.update();
}

/**
 * Called once Google Earth has loaded.
 */
function initCB(instance) 
{
    // retain reference to GEPlugin instance
    earth = instance;

    // specify the speed at which the camera moves
    earth.getOptions().setFlyToSpeed(100);

    // show buildings
    earth.getLayerRoot().enableLayerById(earth.LAYER_BUILDINGS, true);

    // disable terrain (so that Earth is flat)
    earth.getLayerRoot().enableLayerById(earth.LAYER_TERRAIN, false);

    // prevent mouse navigation in the plugin
    earth.getOptions().setMouseNavigationEnabled(false);

    // instantiate shuttle
    shuttle = new Shuttle({
        heading: HEADING,
        height: HEIGHT,
        latitude: LATITUDE,
        longitude: LONGITUDE,
        planet: earth,
        seats: SEATS,
        velocity: VELOCITY
    });

    // synchronize camera with Earth
    google.earth.addEventListener(earth, "frameend", frameend);

    // synchronize map with Earth
    google.earth.addEventListener(earth.getView(), "viewchange", viewchange);

    // update shuttle's camera
    shuttle.updateCamera();

    // show Earth
    earth.getWindow().setVisibility(true);

    // render seating chart
    chart();

    // populate Earth with passengers and houses
    populate();
}

/**
 * Handles keystrokes.
 */
function keystroke(event, state)
{
    // ensure we have event
    if (!event)
    {
        event = window.event;
    }
    
    // upon movement reset announcement board and speedometer
    $("#announcements").html("No announcements at this time!   -   Current Score: " + POINTS);
    $("#speedometer").html("Shuttle Speed: " + shuttle.velocity)
    // left arrow
    if (event.keyCode == 37)
    {
        shuttle.states.turningLeftward = state;
        return false;
    }

    // up arrow
    else if (event.keyCode == 38)
    {
        shuttle.states.tiltingUpward = state;
        return false;
    }

    // right arrow
    else if (event.keyCode == 39)
    {
        shuttle.states.turningRightward = state;
        return false;
    }

    // down arrow
    else if (event.keyCode == 40)
    {
        shuttle.states.tiltingDownward = state;
        return false;
    }

    // A, a
    else if (event.keyCode == 65 || event.keyCode == 97)
    {
        shuttle.states.slidingLeftward = state;
        return false;
    }

    // D, d
    else if (event.keyCode == 68 || event.keyCode == 100)
    {
        shuttle.states.slidingRightward = state;
        return false;
    }
  
    // S, s
    else if (event.keyCode == 83 || event.keyCode == 115)
    {
        shuttle.states.movingBackward = state;     
        return false;
    }

    // W, w
    else if (event.keyCode == 87 || event.keyCode == 119)
    {
        shuttle.states.movingForward = state;    
        return false;
    }
  
    // increase velocity U, u
    else if (event.keyCode == 85 || event.keyCode == 117)
    {
        if (shuttle.velocity == 1000)
        {
            $("#speedometer").html("Shuttle can't go any faster!");
            return false;
        }
        else
        {
            shuttle.velocity += 50;
            $("#speedometer").html("Shuttle Speed: " + shuttle.velocity);
            return false;
        }
    }
    
    // decrease velocity J, j
    else if (event.keyCode == 74 || event.keyCode == 106)
    {
        // ensure velocity stays above zero
        if (shuttle.velocity < 55)
        {
            $("#speedometer").html("Shuttle can't go any slower!");
            return false;
        }
        else
        {
            shuttle.velocity -= 50;
            $("#speedometer").html("Shuttle Speed: " + shuttle.velocity)
            return false;
        }
    }
    return true;
}

/**
 * Sorts shuttle.seats by house name
 * Modified source code from
 * https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Array/sort
 * http://stackoverflow.com/questions/1129216/sorting-objects-in-an-array-by-a-field-value-in-javascript
 */
function sortseats(a, b)
{
    // handle null values in object
    if (a === null|| b === null)
    {
        return 0;
    }
    if (a.house < b.house)
    {
        return -1;
    }
    if (a.house > b.house)
    {
        return 1;
    }
    
    return 0;
}
/**
 * Loads application.
 */
function load()
{
    // embed 2D map in DOM
    var latlng = new google.maps.LatLng(LATITUDE, LONGITUDE);
    map = new google.maps.Map($("#map").get(0), {
        center: latlng,
        disableDefaultUI: true,
        mapTypeId: google.maps.MapTypeId.ROADMAP,
        scrollwheel: false,
        zoom: 17,
        zoomControl: true
    });

    // prepare shuttle's icon for map
    bus = new google.maps.Marker({
        icon: "https://maps.gstatic.com/intl/en_us/mapfiles/ms/micons/bus.png",
        map: map,
        title: "you are here"
    });

    // embed 3D Earth in DOM
    google.earth.createInstance("earth", initCB, failureCB);
}

/**
 * Picks up nearby passengers.
 */
function pickup()
{
    var pickups = 0;
    var freshman = 0;
      
    // loop through all passengers in passgers array check d
    for (var x in PASSENGERS)
    {
        var lat = PASSENGERS[x].placemark.getGeometry().getLatitude();
        var lng = PASSENGERS[x].placemark.getGeometry().getLongitude();
        
        // calculate the distance from the current position of shuttle
        var d = shuttle.distance(lat, lng);
        
        if (d <= 15)
        {
            // check that passenger is not a freshman
            if (HOUSES[PASSENGERS[x].house] === undefined)
            {
                // must be a freshman, skip them
                freshman += 1;
                $("#announcements").html("No freshman are allowed to ride!");
                continue;
            }
            if (SEATS < 1)
            {
                $("#announcements").html("No seats are left, sorry!");
                return;
            }
            for (var i in shuttle.seats)
            {
                if (shuttle.seats[i] == null)
                {
                    var person = {
                        name: PASSENGERS[x].name,
                        house: PASSENGERS[x].house
                    };
                    // add passenger(s) to shuttle
                    //person["name"] = PASSENGERS[x].name;
                    //person["house"] = PASSENGERS[x].house;
                    
                    shuttle.seats[i] = person;
                    
                    // adjust number of seats left and pickups
                    SEATS -= 1;
                    pickups += 1;
                    
                    // remove 3d world placemark
                    var features = earth.getFeatures();
                    features.removeChild(PASSENGERS[x].placemark);
                    
                    // remove 2d world marker
                    PASSENGERS[x].marker.setMap(null);
                    
                    // remove passenger from passenger array
                    PASSENGERS.splice(x, 1);
                    
                    // display passengers in the shuttle
                    chart();
                    
                    break;
                }
            }
            
        }
    }
    if (pickups === 0)
    {
        // announce to user
        $("#announcements").html("Nobody available to pick up!   -   Current Score: " + POINTS);
    }
    else
    {
        $("#announcements").html("You made a pickup!   -   Current Score: " + POINTS);
    }
    if (freshman === 1)
    {
        $("#announcements").html("A freshman was told to walk!   -   Current Score: " + POINTS);
    }
    else if (freshman > 1)
    {
        $("#announcements").html("A few freshmen were told to walk!   -   Current Score: " + POINTS);
    }
}

/**
 * Populates Earth with passengers and houses.
 */
function populate()
{
    // mark houses
    for (var house in HOUSES)
    {
        // plant house on map
        new google.maps.Marker({
            icon: "https://google-maps-icons.googlecode.com/files/home.png",
            map: map,
            position: new google.maps.LatLng(HOUSES[house].lat, HOUSES[house].lng),
            title: house
        });
    }

    // get current URL, sans any filename
    var url = window.location.href.substring(0, (window.location.href.lastIndexOf("/")) + 1);

    // scatter passengers
    for (var i = 0; i < PASSENGERS.length; i++)
    {   
        /*var lat = HOUSES[PASSENGERS[i].house].lat;
        var lng = HOUSES[PASSENGERS[i].house].lng;
        var dist;
        
        do
        {

            
            dist = building.bdistance(lat, lng);
        }
        while (dist < 30);*/

        // pick a random building
        var building = BUILDINGS[Math.floor(Math.random() * BUILDINGS.length)];

        // prepare placemark
        var placemark = earth.createPlacemark("");
        placemark.setName(PASSENGERS[i].name + " to " + PASSENGERS[i].house);

        // prepare icon
        var icon = earth.createIcon("");
        icon.setHref(url + "/img/" + PASSENGERS[i].username + ".jpg");

        // prepare style
        var style = earth.createStyle("");
        style.getIconStyle().setIcon(icon);
        style.getIconStyle().setScale(4.0);

        // prepare stylemap
        var styleMap = earth.createStyleMap("");
        styleMap.setNormalStyle(style);
        styleMap.setHighlightStyle(style);

        // associate stylemap with placemark
        placemark.setStyleSelector(styleMap);

        // prepare point
        var point = earth.createPoint("");
        point.setAltitudeMode(earth.ALTITUDE_RELATIVE_TO_GROUND);
        point.setLatitude(building.lat);
        point.setLongitude(building.lng);
        point.setAltitude(0.0);

        // associate placemark with point
        placemark.setGeometry(point);

        // add placemark to Earth
        earth.getFeatures().appendChild(placemark);

        // add marker to map
        var marker = new google.maps.Marker({
            icon: "https://maps.gstatic.com/intl/en_us/mapfiles/ms/micons/man.png",
            map: map,
            position: new google.maps.LatLng(building.lat, building.lng),
            title: PASSENGERS[i].name + " at " + building.name
        });

        // TODO: remember passenger's placemark and marker for pick-up's sake
        PASSENGERS[i]["placemark"] = placemark;
        PASSENGERS[i]["marker"] = marker;
    }
}

/**
 * Handler for Earth's viewchange event.
 */
function viewchange() 
{
    // keep map centered on shuttle's marker
    var latlng = new google.maps.LatLng(shuttle.position.latitude, shuttle.position.longitude);
    map.setCenter(latlng);
    bus.setPosition(latlng);
}

/**
 * Unloads Earth.
 */
function unload()
{
    google.earth.removeEventListener(earth.getView(), "viewchange", viewchange);
    google.earth.removeEventListener(earth, "frameend", frameend);
}
