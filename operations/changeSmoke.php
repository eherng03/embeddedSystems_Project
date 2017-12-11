<?php

    include "../models/SmokeDBController.php";
   
    $place = $_GET["place"];
    $humi = $_GET["state"];

    $controller = SmokeDBController::getInstance();
   
    $result = $controller->changeStatus($state, $place);
    
?>