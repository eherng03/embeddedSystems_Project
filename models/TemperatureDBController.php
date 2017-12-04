<?php
	include_once "../dataBase/DBManager.php";


	//Clase que controla la tabla de luces de la base de datos
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
		* Cambia el valor de la temperatura de place
		*/
		function changeStatus($value, $place){
			$dbManager = DBManager::getInstance();
			$connection = $dbManager->getConnection();

			$query = $connection->query("UPDATE temperature SET value = '$value' WHERE location = '$place'");
			return $query;
		}
	}
?>