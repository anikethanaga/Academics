function validate()
    {
        var firstName= document.getElementById("fn");
        var lastName=document.getElementById("ln");
        var Email=document.getElementById("email").value;
        var rd1=document.getElementById("r1");
        var rd2=document.getElementById("r2");
        var rd3=document.getElementById("r3");
        var comments=document.getElementById("tx").value;
        var val;
        var regx=/^([a-zA-Z0-9\.-]+)@([a-zA-Z0-9-]+).([a-zA-Z]+)(.[a-z]{2,8})?$/;
        if(firstName.value.trim().length==0 || lastName.value.trim().length==0){alert("No fields can be blank ")}
        if (firstName.value.trim().length>20){alert("maximum length of first name excedeed!");}
        if(lastName.value.trim().length>20){alert("maximum length of last name excedeed!");}
        if(!regx.test(Email)){alert("invalid Email");}
        if(rd1.checked==true){val=rd1.value;}
        else if(rd2.checked==true)val=rd2.value;
        else    val=rd3.value;

        txt="Name= "+(firstName.value+" "+lastName.value)+"<br/>"+"Email= "+Email+"<br/>"+"Gender= "+val+"<br/>"+"Comments: "+comments;

        document.getElementById("l1").innerHTML="Details filled above are "+ "<br/> " +txt;
        return false;
    }