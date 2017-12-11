<?php

    include "../models/TemperatureDBController.php";
   
    $place = $_GET["place"];
    $temp = $_GET["temp"];

    $controller = TemperatureDBController::getInstance();
   
    $result = $controller->changeStatus($temp, $place);
    
?>