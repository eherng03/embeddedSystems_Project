$(document).ready(function() {

/**

LIGHT

**/
	//Comprueba el estado de las luces para actualizar el estado del interruptor
	$.get( "operations/getLightStatus.php", { place: "room"} )
	  .done(function( data ) {
	  	var state = JSON.parse(data);

	    if(state == 1){
        	$("#lightSwitchRoom").attr("checked", true);
        }else if(state == 0){
        	$("#lightSwitchRoom").attr("checked", false);
        }
	 });

	//Comprueba el estado de las luces para actualizar el estado del interruptor
	$.get( "operations/getLightStatus.php", { place: "bathroom"} )
	  .done(function( data ) {
	  	var state = JSON.parse(data);

	    if(state == 1){
        	$("#lightSwitchBath").attr("checked", true);
        }else if(state == 0){
        	$("#lightSwitchBath").attr("checked", false);
        }
	 });


	//Comprueba el estado de las luces para actualizar el estado del interruptor
	$.get( "operations/getLightStatus.php", { place: "garage"} )
	  .done(function( data ) {
	  	var state = JSON.parse(data);

	    if(state == 1){
        	$("#lightSwitchGar").attr("checked", true);
        }else if(state == 0){
        	$("#lightSwitchGar").attr("checked", false);
        }
	 });

	 //Comprueba el estado de las luces para actualizar el estado del interruptor
	$.get( "operations/getLightStatus.php", { place: "kitchen"} )
	  .done(function( data ) {
	  	var state = JSON.parse(data);

	    if(state == 1){
        	$("#lightSwitchKit").attr("checked", true);
        }else if(state == 0){
        	$("#lightSwitchKit").attr("checked", false);
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

/**

DOOR

**/

	 //Compruebo el estado de la puerta para actualiza el estado del interruptor
	$.get( "operations/getDoorStatus.php", { place: "garage"} )
	  .done(function( data ) {
	  	var state = JSON.parse(data);

	    if(state == 1){
        	$("#doorSwitchGar").attr("checked", true);
        }else if(state == 0){
        	$("#doorSwitchGar").attr("checked", false);
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
	                alert("Se ha cerrado la puerta");
	            }
        	});
	    }
	});

/**

PRESENCE

**/
	$.get( "operations/getPresenceInfo.php", { place: "room"} )
  .done(function( data ) {
  	var date = JSON.parse(data);
  	//LOS DATOS SE PROCESAN MAL; NO COMO FECHAS
  	var tabla = document.getElementById("presenceRoomTable");

  	date.forEach((fecha) =>{
            var row = document.createElement('tr');
           	var td = document.createElement('td');
            td.innerHTML = fecha;
            row.appendChild(td);
            tabla.appendChild(row);
        });

 	});

  $.get( "operations/getPresenceInfo.php", { place: "garage"} )
  .done(function( data ) {
  	var date = JSON.parse(data);
  	//LOS DATOS SE PROCESAN MAL; NO COMO FECHAS
  	var tabla = document.getElementById("presenceGarageTable");

  	date.forEach((fecha) =>{
            var row = document.createElement('tr');
           	var td = document.createElement('td');
            td.innerHTML = fecha;
            row.appendChild(td);
            tabla.appendChild(row);
        });

 	});


  /**

SMOKE

**/
	$.get( "operations/getSmokeInfo.php", { place: "kitchen"} )
  .done(function( data ) {
  	var date = JSON.parse(data);
  	//LOS DATOS SE PROCESAN MAL; NO COMO FECHAS
  	var tabla = document.getElementById("kitchenSmokeTable");

  	date.forEach((fecha) =>{
            var row = document.createElement('tr');
           	var td = document.createElement('td');
            td.innerHTML = fecha;
            row.appendChild(td);
            tabla.appendChild(row);
        });

 	});

  $.get( "operations/getSmokeInfo.php", { place: "garage"} )
  .done(function( data ) {
  	var date = JSON.parse(data);
  	//LOS DATOS SE PROCESAN MAL; NO COMO FECHAS
  	var tabla = document.getElementById("garageSmokeTable");

  	date.forEach((fecha) =>{
            var row = document.createElement('tr');
           	var td = document.createElement('td');
            td.innerHTML = fecha;
            row.appendChild(td);
            tabla.appendChild(row);
        });

 	});

  /**

  /**

TEMPERATURE

**/
	$.get( "operations/getTemperature.php", { place: "kitchen"} )
  .done(function( data ) {
  	var temp = JSON.parse(data);
  	//LOS DATOS SE PROCESAN MAL; NO COMO FECHAS
  	var label = document.getElementById("kitchenTemp");
  	var string = "Temperatura: " + temp + "ºC";
  	label.innerHTML = string;

 	});

  $.get( "operations/getTemperature.php", { place: "bathroom"} )
  .done(function( data ) {
  	var temp = JSON.parse(data);
  	//LOS DATOS SE PROCESAN MAL; NO COMO FECHAS
  	var label = document.getElementById("bathTemp");
  	var string = "Temperatura: " + temp + "ºC";
  	label.innerHTML = string;

 	});

    /**

humedad

**/
	$.get( "operations/getHumidity.php", { place: "kitchen"} )
  .done(function( data ) {
  	var temp = JSON.parse(data);
  	//LOS DATOS SE PROCESAN MAL; NO COMO FECHAS
  	var label = document.getElementById("kitchenHum");
  	var string = "Humedad: " + temp + "%";
  	label.innerHTML = string;

 	});

  $.get( "operations/getHumidity.php", { place: "bathroom"} )
  .done(function( data ) {
  	var hum = JSON.parse(data);
  	//LOS DATOS SE PROCESAN MAL; NO COMO FECHAS
  	var label = document.getElementById("bathHum");
  	var string = "Humedad: " + hum + "%";
  	label.innerHTML = string;

 	});

});

