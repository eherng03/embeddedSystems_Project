<?php
	include_once "../dataBase/DBManager.php";


	//Clase que controla la tabla de humedad de la base de datos
	class HumidityDBController{
		private static $instance;
		private function __construct(){}
		
		public static function getInstance(){
			if (!self::$instance instanceof self){
				self::$instance = new self;
			}
			return self::$instance;
		}

		/**
		Inserta el dato de humedad de la habitacion place
		*/
		function changeStatus($humi, $place){
			$dbManager = DBManager::getInstance();
			$connection = $dbManager->getConnection();

			$query = $connection->query("INSERT INTO humidity (place, date, value) VALUES ('$place', CURRENT_TIMESTAMP, '$humi')");
			return $query;
		}

		/**
		Devuelve las temperatura de un determinado sitio
		*/
		function getInfo($place){
			$dbManager = DBManager::getInstance();
			$connection = $dbManager->getConnection();

			$query = $connection->query("SELECT * FROM humidity WHERE place = '$place'");
			return $query;
		}
	}
?>