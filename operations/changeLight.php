<?php  

	include "../models/LightsDBController.php";

	$state = $_POST['state'];
	$place = $_POST['place'];

	

	$controller = LightsDBController::getInstance();

	$result = $controller->changeStatus($state, $place);
/*
	if($result){
		print_r("Bieeeen");
	}else{
		print_r("Error al cambiar la luz.");
	}
	*/
?>