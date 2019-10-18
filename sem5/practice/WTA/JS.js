
function add(x,y) {
        return(x+y);
}
<script>
        console.log("javascript is working");
        document.write("add(3,4) is " + add(3,4) + "<BR>");
        document.write("add(\"3\",\"4\") is " + add("3","4") +"<BR>");
        document.write("add(\"Hi\",\"Dave\") is " +add("Hi","Dave") + "<BR>");
        document.write("add(3,\"Hi\") is " + add(3,"Hi") +"<BR>");
        document.write("add(\"2.13blah\",3.14) is " +add("2.13blah",3.14));
</script>