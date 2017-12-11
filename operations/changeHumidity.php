<?php

    include "../models/HumidityDBController.php";
   
    $place = $_GET["place"];
    $humi = $_GET["hum"];

    $controller = HumidityDBController::getInstance();
   
    $result = $controller->changeStatus($humi, $place);
    
?>