<?php  

	include "../models/LightsDBController.php";

	$place = $_GET['place'];

	

	$controller = PresenceDBController::getInstance();

	$result = $controller->getInfo($place);

	$date = array();
    //guardados todos los datos como object destino
    while($row = $result->fetch_array()){
         $date = $row;
    }
    //devuelve horas al js
    echo json_encode($date);

	
?>