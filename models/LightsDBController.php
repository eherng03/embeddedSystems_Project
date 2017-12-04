<?php
	include_once "../dataBase/DBManager.php";


	//Clase que controla la tabla de luces de la base de datos
	class LightsDBController{
		private static $instance;
		private function __construct(){}
		
		public static function getInstance(){
			if (!self::$instance instanceof self){
				self::$instance = new self;
			}
			return self::$instance;
		}

		/**
		Cambia el estado de las luces de la habitacion place
		*/
		function changeStatus($state, $place){
			$dbManager = DBManager::getInstance();
			$connection = $dbManager->getConnection();

			$query = $connection->query("UPDATE light SET state = '$state' WHERE place = '$place'");
			return $query;
		}

		/**
		Cambia el estado de las luces de la habitacion place
		*/
		function checkStatus($place){
			$dbManager = DBManager::getInstance();
			$connection = $dbManager->getConnection();

			$query = $connection->query("SELECT state FROM light WHERE place = '$place'");
			return $query;
		}

	}
?>