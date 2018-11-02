function likeImage(ob) {
    try {
        if (1)//(navigator.userAgent.search("Firefox") > -1)
            location.href = 'comments.php?action=like&id=' +ob.value;
        else {
            $.ajaxSetup({
                cache: false
            });
            $.ajax({
                type: 'GET',
                url: "comments.php",
                data: {action: 'like', id: ob.value},
                success: function (data) {
                    console.log(data);
                }
            });
            location.reload();
        }
    }
    catch (err) {
        alert('Wait something\'s not right: '+ err);
    }
    return false;
}
function submitComment(ob) {
    try {
        var comment = document.querySelector("textarea[name='"+ ob.value +"']");
        if (1)//(navigator.userAgent.search("Firefox") > -1)
            location.href = 'comments.php?action=comment&id=' +ob.value + '&comment=' +comment.value;
        else {
            $.ajaxSetup({
                cache: false
            });
            $.ajax({
                type: 'GET',
                url: "comments.php",
                data: {action: 'comment', id: ob.value, message: comment.value},
                success: function (data) {
                    console.log(data);
                    location.reload();
                }
            });
            location.reload();
        }

    } catch (err) {
        alert('Wait something\'s not right: ' + err);
    }
    return false;
}