// $("#top a").click(function() {
//
//   $("#top a").removeClass(); // Removes existing classes
//
//   var linkTitle = $(this).attr("title");
//
//   if (linkTitle == "Brown") {
//
//     $(this).addClass("brown"); // You can add the class to something else
//
//   }
// });



$('#btnClick').on('click', function () {
    if ($('#1').css('display') != 'none') {
        $('#2').show().siblings('div').hide();
    } else if ($('#2').css('display') != 'none') {
        $('#1').show().siblings('div').hide();
    }
});

$(".navbar a").on("click", function(){
   $(".navbar").find(".active").removeClass("active");
   $(this).parent().addClass("active");
});


//Image uplaod things
$("#profileImage").click(function (e) {
    $("#imageUpload").click();
});

function fasterPreview(uploader) {
    if (uploader.files && uploader.files[0]) {
        $('#profileImage').attr('src',
            window.URL.createObjectURL(uploader.files[0]));
    }
}

$("#imageUpload").change(function () {
    fasterPreview(this);
});