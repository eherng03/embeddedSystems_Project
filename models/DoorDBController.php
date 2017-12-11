<?php
	include_once "../dataBase/DBManager.php";


	//Clase que controla la tabla de puerta de la base de datos
	class DoorDBController{
		private static $instance;
		private function __construct(){}
		
		public static function getInstance(){
			if (!self::$instance instanceof self){
				self::$instance = new self;
			}
			return self::$instance;
		}

		/**
		Cambia el estado de las luces del lugar place
		*/
		function changeStatus($state, $place){
			$dbManager = DBManager::getInstance();
			$connection = $dbManager->getConnection();

			$query = $connection->query("UPDATE door SET state = '$state' WHERE place = '$place'");
			return $query;
		}

		/**
		Cambia el estado de las luces del lugar place
		*/
		function checkStatus($place){
			$dbManager = DBManager::getInstance();
			$connection = $dbManager->getConnection();

			$query = $connection->query("SELECT state FROM door WHERE place = '$place'");
			return $query;
		}

	}
?>