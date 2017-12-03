$(document).ready(function() {

	//Encender y apagar la luz de la habitación
	$("#lightSwitchRoom").change(function() {
	    if($(this).is(":checked")) {
	        $.ajax({
	            url: "operations/changeLight.php",
	            type: 'POST',
	            data: {"state": "1", "place": "room"},
	            
	            success: function(data){
	                alert(data);
	            }
        	});
	    }else{
	    	$.ajax({
	            url: "operations/changeLight.php",
	            type: 'POST',
	            data: {"state": "0", "place": "room"},
	            
	            success: function(data){
	                alert("Se ha apagado la luz");
	            }
        	});
	    }
	});

	//Encender y apagar la luz del baño
	$("#lightSwitchBath").change(function() {
	    if($(this).is(":checked")) {
	        $.ajax({
	            url: "operations/changeLight.php",
	            type: 'POST',
	            data: {"state": "1", "place": "bathroom"},
	            
	            success: function(data){
	                alert(data);
	            }
        	});
	    }else{
	    	$.ajax({
	            url: "operations/changeLight.php",
	            type: 'POST',
	            data: {"state": "0", "place": "bathroom"},
	            
	            success: function(data){
	                alert("Se ha apagado la luz");
	            }
        	});
	    }
	});

	//Encender y apagar la luz del baño
	$("#lightSwitchGar").change(function() {
	    if($(this).is(":checked")) {
	        $.ajax({
	            url: "operations/changeLight.php",
	            type: 'POST',
	            data: {"state": "1", "place": "garaje"},
	            
	            success: function(data){
	                alert(data);
	            }
        	});
	    }else{
	    	$.ajax({
	            url: "operations/changeLight.php",
	            type: 'POST',
	            data: {"state": "0", "place": "garaje"},
	            
	            success: function(data){
	                alert("Se ha apagado la luz");
	            }
        	});
	    }
	});

	//Encender y apagar la luz de la cocina
	$("#lightSwitchKit").change(function() {
	    if($(this).is(":checked")) {
	        $.ajax({
	            url: "operations/changeLight.php",
	            type: 'POST',
	            data: {"state": "1", "place": "kitchen"},
	            
	            success: function(data){
	                alert(data);
	            }
        	});
	    }else{
	    	$.ajax({
	            url: "operations/changeLight.php",
	            type: 'POST',
	            data: {"state": "0", "place": "kitchen"},
	            
	            success: function(data){
	                alert("Se ha apagado la luz");
	            }
        	});
	    }
	});
});

