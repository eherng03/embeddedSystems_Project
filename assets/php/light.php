<?php  

	$state = $_POST['state'];

	if ($state = 'encender') { 
		$a- exec("sudo python ../scripts/on.py");
		echo $a;
	}

	if ($state = 'encender') { 
		$a- exec("sudo python ../scripts/off.py");
		echo $a;
	}
?>