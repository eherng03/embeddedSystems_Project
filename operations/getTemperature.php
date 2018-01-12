<?php  

	include "../models/TemperatureDBController.php";

	$place = $_GET['place'];

	$controller = TemperatureDBController::getInstance();

	$result = $controller->getInfo($place);

	$temp = array();
    while($row = $result->fetch_array()){
    	$temp = $row['value'];
    }
    
    echo json_encode($temp);

?>