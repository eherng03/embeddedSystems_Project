<?php  

	include "../models/DoorDBController.php";

	$place = $_GET['place'];

	

	$controller = DoorDBController::getInstance();

	$result = $controller->checkStatus($place);

	$state = array();
    //guardados todos los datos como object destino
    while($row = $result->fetch_array()){
         $state = $row;
    }
    //echo '<pre>'; print_r($driver); echo '</pre>';
    echo json_encode($state);

	
?>