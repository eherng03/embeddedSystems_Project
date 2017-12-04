<?php
	include_once "../dataBase/DBManager.php";


	//Clase que controla la tabla de luces de la base de datos
	class PlaceDBController{
		private static $instance;
		private function __construct(){}
		
		public static function getInstance(){
			if (!self::$instance instanceof self){
				self::$instance = new self;
			}
			return self::$instance;
		}

	}
?>