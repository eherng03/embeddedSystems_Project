<?php
	include_once "../dataBase/DBManager.php";


	//Clase que controla la tabla de humo de la base de datos
	class SmokeDBController{
		private static $instance;
		private function __construct(){}

		public static function getInstance(){
			if (!self::$instance instanceof self){
				self::$instance = new self;
			}
			return self::$instance;
		}

		/**
		Inserta un nuevo dato de humo de la habitacion place
		*/
		function changeStatus($state, $place){
			$dbManager = DBManager::getInstance();
			$connection = $dbManager->getConnection();

			$query = $connection->query("INSERT INTO smoke (status, date, place) VALUES ($state, CURRENT_TIMESTAMP, '$place')");
			return $query;
		}

		/**
		Devuelve las horas a las que se ha detectado presencia
		*/
		function getInfo($place){
			$dbManager = DBManager::getInstance();
			$connection = $dbManager->getConnection();

			$query = $connection->query("SELECT * FROM smoke WHERE place = '$place' AND status = '1'");
			return $query;
		}
	}
?>
