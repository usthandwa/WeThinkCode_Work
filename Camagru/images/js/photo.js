(function () {
    var video = document.getElementById('video'),
        canvas = document.getElementById('canvas'),
        context = canvas.getContext('2d'),
        vendorUrl = window.URL || window.webkitURL;
    context.translate(canvas.width, 0);
    context.scale(-1,1);
    navigator.getMedia =    navigator.getUserMedia ||
        navigator.webkitGetUserMedia ||
        navigator.mozGetUserMedia ||
        navigator.mediaDevices.getUserMedia||
        navigator.msGetUserMedia;
    navigator.getMedia({
        video: true,
        audio: false
    }, function (stream) {
        try {
            video.srcObject = stream;
        } catch (error) {
            video.src = vendorUrl.createObjectURL(stream);
        }
        video.play();
    }, function () {
        alert('Unable to find camera. Please upload an image.');
        location.href = 'Gallery.php';
    });
    if (document.getElementById('snap')) {
        document.getElementById('snap').addEventListener('click', function () {
            var subimage = document.getElementById('sub-image');
            context.drawImage(video, 0, 0, 500, 375);

            subimage.value = canvas.toDataURL();
            document.getElementById('submit-form');

            var img = new Image();
            img.onload = function () {
                var ctx = document.getElementById('canvas').getContext('2d');
                ctx.translate(canvas.width, 0);
                ctx.scale(-1,1);
                ctx.drawImage(img, 0, 0);
            }
            // img.src = 'temp/img.jpg';
        });
    }
})();


var fileUpload = document.getElementById('fileToUpload');
var canvas  = document.getElementById('canvas');
var ctx = canvas.getContext("2d");
var subimage = document.getElementById('up-image');

function readImage() {
    if ( this.files && this.files[0] ) {
        var FR= new FileReader();
        FR.onload = function(e) {
            var img = new Image();
            img.src = e.target.result;
            img.onload = function() {
                ctx.drawImage(img, 0, 0, 500, 375);
                var dataurl = canvas.toDataURL();
                document.getElementById('canvas').src = dataurl;
                subimage.value = dataurl;
            };
        };
        FR.readAsDataURL( this.files[0] );
    }
}

fileUpload.onchange = readImage;

