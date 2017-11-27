$(document).ready(function() {
	$("#lightSwitch").change(function() {
	    if($(this).is(":checked")) {
	        $.ajax({
	            url: "assets/php/light.php",
	            type: 'POST',
	            data: {"state": "on"},
	            
	            success: function(data){
	                alert("Se ha encendido la luz");
	            }
        	});
	    }else{
	    	$.ajax({
	            url: "assets/php/light.php",
	            type: 'POST',
	            data: {"state": "off"},
	            
	            success: function(data){
	                alert("Se ha apagado la luz");
	            }
        	});
	    }
	});
});