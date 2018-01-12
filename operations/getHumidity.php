<?php  

	include "../models/HumidityDBController.php";

	$place = $_GET['place'];

	$controller = HumidityDBController::getInstance();

	$result = $controller->getInfo($place);

	$hum = array();
    while($row = $result->fetch_array()){
    	$hum = $row['value'];
    }
    
    echo json_encode($hum);

?>