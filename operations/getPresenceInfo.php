<?php  

	include "../models/PresenceDBController.php";

	$place = $_GET['place'];

	

	$controller = PresenceDBController::getInstance();

	$result = $controller->getInfo($place);

	$date = array();
    //guardados todos los datos como object destino
    while($row = $result->fetch_array()){
         array_push($date, $row['date']);
    }
    //devuelve horas al js
    echo json_encode($date);

	
?>