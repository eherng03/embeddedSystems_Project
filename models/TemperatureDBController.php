<?php
	include_once "../dataBase/DBManager.php";


	//Clase que controla la tabla de temperatura de la base de datos
	class TemperatureDBController{
		private static $instance;
		private function __construct(){}
		
		public static function getInstance(){
			if (!self::$instance instanceof self){
				self::$instance = new self;
			}
			return self::$instance;
		}

		/**
		Inserta un nuevo dato de temperatura de la habitacion place
		*/
		function changeStatus($temp, $place){
			$dbManager = DBManager::getInstance();
			$connection = $dbManager->getConnection();

			$query = $connection->query("UPDATE temperature SET value = $temp, date = CURRENT_TIMESTAMP WHERE place = '$place'");
			return $query;

		}

		/**
		Devuelve las temperatura de un determinado sitio
		*/
		function getInfo($place){
			$dbManager = DBManager::getInstance();
			$connection = $dbManager->getConnection();

			$query = $connection->query("SELECT * FROM temperature WHERE place = '$place'");
			return $query;
		}
	}
?>