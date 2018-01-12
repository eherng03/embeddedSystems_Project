<?php  

	include "../models/PresenceDBController.php";

	$place = $_GET['place'];

	setlocale(LC_ALL,"esp");

	$controller = PresenceDBController::getInstance();

	$result = $controller->getInfo($place);

	$date = array();
    //guardados todos los datos como object destino
    while($row = $result->fetch_array()){

    	$fecha = date("d/m/Y H:i:s", strtotime($row['date']));
        array_push($date, $fecha);
    }
    //devuelve horas al js
    echo json_encode($date);

	
?>