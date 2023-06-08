<?php

/* Check if the status exists */
if (isset($_GET['status']))
{	
	/* Check for the status */
	if( $_GET['status'] == 'app1')
	{
		/* Open APP 1 file */
		$app1 = fopen("app1.txt","r");
		
		/* Loop till the end of the file */
		while(!feof($app1))
		{	
			/* Open Buffer & Overwrite */
			$buffer = fopen("buffer.txt","w");
			
			/* Write line from app1 in buffer */
			fputs($buffer,fgets($app1));
			
			/* Loop until ok is received */
			while( !($_GET['response'] == 'ok') );
			
			/* Close Buffer File */
			fclose($buffer);
		}
		
		/* Open Buffer & Overwrite */
		$buffer = fopen("buffer.txt","w");
		
		/* Write done in buffer */
		fwrite($buffer,"done");
		
		/* Loop until ok is received */
		while( !($_GET['response'] == 'ok') );
		
		/* Close APP 1 File */
		fclose($app1);
		
		/* Close Buffer File */
		fclose($buffer);
		
		/* Go to APP 1 Page */
		header("Location: app1.html");
	}
	else if( $_GET['status'] == 'app2')
	{
		/* Open APP 2 file */
		$app1 = fopen("app2.txt","r");
		
		/* Loop till the end of the file */
		while(!feof($app2))
		{	
			/* Open Buffer & Overwrite */
			$buffer = fopen("buffer.txt","w");
			
			/* Write line from app2 in buffer */
			fputs($buffer,fgets($app2));
			
			/* Loop until ok is received */
			while( !($_GET['response'] == 'ok') );
			
			/* Close Buffer File */
			fclose($buffer);
		}
		
		/* Open Buffer & Overwrite */
		$buffer = fopen("buffer.txt","w");
		
		/* Write done in buffer */
		fwrite($buffer,"done");
		
		/* Loop until ok is received */
		while( !($_GET['response'] == 'ok') );
		
		/* Close APP 2 File */
		fclose($app2);
		
		/* Close Buffer File */
		fclose($buffer);
		
		/* Go to APP 2 Page */
		header("Location: app2.html");
	}
	else if( $_GET['status'] == 'app3')
	{
		/* Open APP 3 file */
		$app1 = fopen("app3.txt","r");
		
		/* Loop till the end of the file */
		while(!feof($app3))
		{	
			/* Open Buffer & Overwrite */
			$buffer = fopen("buffer.txt","w");
			
			/* Write line from app3 in buffer */
			fputs($buffer,fgets($app3));
			
			/* Loop until ok is received */
			while( !($_GET['response'] == 'ok') );
			
			/* Close Buffer File */
			fclose($buffer);
		}
		
		/* Open Buffer & Overwrite */
		$buffer = fopen("buffer.txt","w");
		
		/* Write done in buffer */
		fwrite($buffer,"done");
		
		/* Loop until ok is received */
		while( !($_GET['response'] == 'ok') );
		
		/* Close APP 3 File */
		fclose($app3);
		
		/* Close Buffer File */
		fclose($buffer);
		
		/* Go to APP 1 Page */
		header("Location: app3.html");
	}
	
}

?>