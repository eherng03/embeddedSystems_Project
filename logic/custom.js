$(document).ready(function() {


	//Comprueba el estado de las luces para actualizar el estado del interruptor
	$.get( "operations/checkLightStatus.php", { place: "room"} )
	  .done(function( data ) {
	  	var datos = JSON.parse(data);
	  	var state = datos.state;

	    if(state == 1){
        	$("#lightSwitchRoom").attr("checked", true);
        }else if(state == 0){
        	$("#lightSwitchRoom").attr("checked", false);
        }
	 });

	//Comprueba el estado de las luces para actualizar el estado del interruptor
	$.get( "operations/checkLightStatus.php", { place: "bathroom"} )
	  .done(function( data ) {
	  	var datos = JSON.parse(data);
	  	var state = datos.state;

	    if(state == 1){
        	$("#lightSwitchBath").attr("checked", true);
        }else if(state == 0){
        	$("#lightSwitchBath").attr("checked", false);
        }
	 });


	//Comprueba el estado de las luces para actualizar el estado del interruptor
	$.get( "operations/checkLightStatus.php", { place: "garage"} )
	  .done(function( data ) {
	  	var datos = JSON.parse(data);
	  	var state = datos.state;

	    if(state == 1){
        	$("#lightSwitchGar").attr("checked", true);
        }else if(state == 0){
        	$("#lightSwitchGar").attr("checked", false);
        }
	 });

	 //Comprueba el estado de las luces para actualizar el estado del interruptor
	$.get( "operations/checkLightStatus.php", { place: "kitchen"} )
	  .done(function( data ) {
	  	var datos = JSON.parse(data);
	  	var state = datos.state;

	    if(state == 1){
        	$("#lightSwitchKit").attr("checked", true);
        }else if(state == 0){
        	$("#lightSwitchKit").attr("checked", false);
        }
	 });

	 //Compruebo el estado de la puerta para actualiza el estado del interruptor
	$.get( "operations/checkDoorStatus.php", { place: "garage"} )
	  .done(function( data ) {
	  	var datos = JSON.parse(data);
	  	var state = datos.state;

	    if(state == 1){
        	$("#doorSwitchGar").attr("checked", true);
        }else if(state == 0){
        	$("#doorSwitchGar").attr("checked", false);
        }
	 });

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
	            data: {"state": "1", "place": "garage"},
	            
	            success: function(data){
	                alert(data);
	            }
        	});
	    }else{
	    	$.ajax({
	            url: "operations/changeLight.php",
	            type: 'POST',
	            data: {"state": "0", "place": "garage"},
	            
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

	// Actualizar el estado de la puerta del garage
	$("#doorSwitchGar").change(function() {
	    if($(this).is(":checked")) {
	        $.ajax({
	            url: "operations/changeDoor.php",
	            type: 'POST',
	            data: {"state": "1", "place": "garage"},
	            
	            success: function(data){
	                alert(data);
	            }
        	});
	    }else{
	    	$.ajax({
	            url: "operations/changeDoor.php",
	            type: 'POST',
	            data: {"state": "0", "place": "garage"},
	            
	            success: function(data){
	                alert("Se ha apagado la luz");
	            }
        	});
	    }
	});
});

