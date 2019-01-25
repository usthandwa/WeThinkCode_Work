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


function select(ob) {
    try {
        console.log(ob);
        $.ajaxSetup({
            cache: false
        });
        $.ajax({
            success: function (data) {
                console.log(data);
            }
        });
    }
    catch (err) {
        alert('Wait something\'s not right: ' + err);
    }
    return false;
}

// <ul id="list">
//                             </ul>
//                             <script>document.getElementById("add").addEventListener("keyup", function (e) {
//                                 if (e.keyCode == 32 || e.key == ' ') {
//                                     txt = document.getElementById("add").value;
//                                     if (txt.split(/[\s, ]+/).length > 2) {
//                                         console.log(txt.split(/[\s, ]+/));
//                                         texts = txt.split(/[\s, ]+/);
//                                         text = texts[texts.length - 2];
//                                         console.log(text + " " + texts.length - 1);
//                                     }
//                                     else
//                                         text = txt;
//                                     delete li;
//                                     li = document.createElement("li");
//                                     li.appendChild(document.createTextNode('#' + text));
//
//                                     document.getElementById("list").appendChild(li);
//                                 }
//                             }, true)
//
//                             </script>