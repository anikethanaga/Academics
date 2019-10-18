images=['file:///home/user/Academics/sem5/labs/WTA/XHTML/images/p1.jpg','file:///home/user/Academics/sem5/labs/WTA/XHTML/images/p2.jpg','file:///home/user/Academics/sem5/labs/WTA/XHTML/images/p3.jpeg','file:///home/user/Academics/sem5/labs/WTA/XHTML/images/p4.jpeg','file:///home/user/Academics/sem5/labs/WTA/XHTML/images/p5.jpg'];
var n=images.length;
function nextImage()
{
    var im=document.getElementById("i1");
    var i;
    for (i=0;i < images.length;i++)
    {
        //alert(images[i]);
        //alert(document.getElementById("i1").src);
        //alert(document.getElementById("i1").src==images[i])
        if(im.src==images[i])
        {
            im.src=images[(i+1)%n];
            break;
        }
    }
}
function prevImage()
{
    var i;
    var im=document.getElementById("i1");
    for (i=0;i < images.length;i++)
    {
        //alert(images[i]);
        //alert(document.getElementById("i1").src);
        //alert(document.getElementById("i1").src==images[i];
        if(im.src==images[i])
        {
            if(i==0)
            {
                im.src=images[images.length-1];
            }
            else
            {
                im.src=images[i-1];
            }
            break;
        }
    }
}