var map, searchManager, x = document.getElementById('location');

function GetMap(lat, lon) {
    map = new Microsoft.Maps.Map('#myMap', {
        credentials: 'ApKJuorXSr9qfGLE3bNIT89Sr-28l7WzbWnoWgyJvPvmX-gYw1QKFTP-7Ib84DQC',
        center: new Microsoft.Maps.Location(lat, lon),
        zoom: 12
    });

    //Make a request to reverse geocode the center of the map.
    reverseGeocode();
}

function reverseGeocode() {
    //If search manager is not defined, load the search module.
    if (!searchManager) {
        //Create an instance of the search manager and call the reverseGeocode function again.
        Microsoft.Maps.loadModule('Microsoft.Maps.Search', function () {
            searchManager = new Microsoft.Maps.Search.SearchManager(map);
            reverseGeocode();
        });
        } else {
        var searchRequest = {
            location: map.getCenter(),
            callback: function (r) {
                //Tell the user the name of the result.
                x.value = r.name;
                console.log(r.name);
            },
            errorCallback: function (e) {
                //If there is an error, alert the user about it.
                console.log("Unable to reverse geocode location.");
            }
        };

        //Make the reverse geocode request.
        searchManager.reverseGeocode(searchRequest);
    }
    }


// BingMapsKey = 'ApKJuorXSr9qfGLE3bNIT89Sr-28l7WzbWnoWgyJvPvmX-gYw1QKFTP-7Ib84DQC';
//
// function getAddress (latitude, longitude) {
//   $.ajax('http://dev.virtualearth.net/REST/v1/Locations/'+ latitude +','+longitude+'??includeEntityTypes=countryRegion&jsonp=MyCallbackFunction&jsonso=abc3144sd&key=' + BingMapsKey)
//   .then(
//     function success (response) {
//       console.log('User\'s Address Data is ', response['country'])
//     },
//     function fail (status) {
//       console.log('Request failed.  Returned status of',
//                   status)
//     }
//    )
// }
function ipLookUp() {
    $.ajax('http://api.ipstack.com/check?access_key=7cf3582503675544e752924eb3142e79&format=1')
  .then(
      function success(response) {
          // console.log('User\'s Location Data is ', response.name);
          console.log('User\'s Country', response);
          GetMap(response.lat, response.lon);
      },

      function fail(data, status) {
          console.log('Request failed.  Returned status of',
              status);
      }
  );
}

function getLocation() {
    if ("geolocation" in navigator) {
        // check if geolocation is supported/enabled on current browser
        navigator.geolocation.getCurrentPosition(
            function success(position) {
                // for when getting location is a success
                console.log('latitude', position.coords.latitude,
                    'longitude', position.coords.longitude);
                GetMap(position.coords.latitude,
                    position.coords.longitude)
            },
            function error(error_message) {
                // for when getting location results in an error
                console.error('An error has occured while retrieving location', error_message);
                ipLookUp()
            });
    } else {
        // geolocation is not supported
        // get your location some other way
        console.log('geolocation is not enabled on this browser');
        ipLookUp()
    }
}


// var x = document.getElementById("mapholder");
//     function getLocation() {
//         if (navigator.geolocation) {
//             console.log(navigator.geolocation);
//             navigator.geolocation.getCurrentPosition(sendPosition);
//         } else {
//             ipLookUp()
//             console.log("Geolocation is not supported by this browser.");
//         }
//     }
//     function sendPosition(position) {
//         var lat = position.coords.latitude;
//         var long = position.coords.longitude;
//         console.log(position);
//
//         x.innerHTML =  position.city + " , " + position.country;
//         x.value = lat + " " + long;
//     }
//     function ipLookUp () {
//   $.ajax('http://api.ipstack.com/check?access_key=7cf3582503675544e752924eb3142e79&format=1')
//   .then(
//       function success(response) {
//           x.innerHTML = response.country + " , " + response.city;
//           console.log('User\'s Location Data is ', response);
//           console.log('User\'s Country', response.country);
//           x.value = response.latitude + " " + response.longitude;
//       },
//       function fail(data, status) {
//           console.log('Request failed.  Returned status of ', status);
//       }
//   );
// }
//
// function getautoLocation() {
//     if (navigator.geolocation) {
//         navigator.geolocation.getCurrentPosition(sendPosition);
//     } else {
//         sendPosition();
//         console.log("Geolocation is not supported by this browser.");
//     }
// }
//
// function send_Position(position) {
//     var lat = position.coords.latitude;
//     var long = position.coords.longitude;
//
//     document.getElementById('location').value = lat + " " + long;
// }
//
// function ip_LookUp() {
//     $.ajax('http://ip-api.com/json')
//         .then(
//             function success(response) {
//                 x.innerHTML = response.country + " , " + response.city;
//                 console.log('User\'s Location Data is ', response);
//                 console.log('User\'s Country', response.country);
//             },
//             function fail(data, status) {
//                 console.log('Request failed.  Returned status of ', status);
//             }
//         );
// }