$(document).ready(function() {
// see if we're at the bottom of the page to potentially load more content
    $(window).on('scroll', scrollProducts);
    var count = 2;

    function scrollProducts() {
        var end = $(document).height() - $(window).height();
        var viewEnd = $(window).scrollTop() + $(window).height();
        var distance = end - viewEnd;

        // when we're almost at the bottom
        if (distance < 300 && count < total) {
            // unbind to prevent excessive firing
            $(window).off('scroll', scrollProducts);
            console.log('we reached the bottom');
            $.ajaxSetup ({
                cache: false
            });
            $.ajax({
                type: 'POST',
                url: "Gallery.php",
                data: {send : count},
                success: function (data) {
                    console.log("success!");
                    $('#content').append(data).fadeIn();
                    // rebind after successful update
                    $(window).on('scroll', scrollProducts);
                    count++;
                }
            });
        }
    }
});