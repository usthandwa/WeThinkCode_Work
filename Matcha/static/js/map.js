var x = document.getElementById("mapholder");
    function getLocation() {
        if (navigator.geolocation) {
            navigator.geolocation.getCurrentPosition(sendPosition);
        } else {
            sendPosition();
            console.log("Geolocation is not supported by this browser.");
        }
    }
    function sendPosition(position) {
        var lat = position.coords.latitude;
        var long = position.coords.longitude;

        x.innerHTML =  position.coords.latitude +
    " += " + position.coords.longitude;
    }
    function ipLookUp () {
  $.ajax('http://ip-api.com/json')
  .then(
      function success(response) {
          x.innerHTML = response.country + " , " + response.city;
          console.log('User\'s Location Data is ', response);
          console.log('User\'s Country', response.country);
      },
      function fail(data, status) {
          console.log('Request failed.  Returned status of ', status);
      }
  );
}