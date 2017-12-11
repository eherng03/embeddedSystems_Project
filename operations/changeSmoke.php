<?php

    include "../models/SmokeDBController.php";
   
    $place = $_GET["place"];
    $humi = $_GET["status"];

    $controller = SmokeDBController::getInstance();
   
    $result = $controller->changeStatus($status, $place);
    
?>