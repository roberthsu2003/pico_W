$(document).ready(function(){    
    $('<ul class="nav navbar-nav">'+
      '<li><a href="index.html">Home</a></li>'+
      '<li><a href="ledControl.html">LEDControll</a></li>'+           
      '<li><a href="pwmled.html">PWM_LED</a></li>'+
      '<li><a href="rgbled.html">RGB_LED</a></li>'+
      '<li><a href="mcp3008.html">MCP3008</a></li>'+
      '<li><a href="servo.html">Servo</a></li>'+
      '</ul>').appendTo('#navbar');
    var pageName = location.pathname.substring(1);
    if(pageName.length == 0){
        pageName = "index.html";
    }
    $("ul.nav>li>a").each(function(i){
        if ($(this).attr("href") == pageName){
            $(this).parent().addClass("active");
        }
    });
});