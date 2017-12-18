<?php

    include "../models/PresenceDBController.php";
   
    $place = $_GET["place"];
    $state = $_GET["state"];

    $controller = PresenceDBController::getInstance();
   
    $result = $controller->changeStatus($state, $place);
    
?>