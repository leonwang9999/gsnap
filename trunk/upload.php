<?php 
     
    $uploadpath = '/hsphere/local/home/sakses/googlestop.com/gsnap/'; 
    $source = $HTTP_POST_FILES['file1']['tmp_name']; 
    $dest = ''; 
	$origninal_name = $HTTP_POST_FILES['file1']['name']; 
	
    if ( ($source != 'none') && ($source != '' )) { 

        $imagesize = getimagesize($source); 

        switch ( $imagesize[2] ) { 

            case 0: 

                echo '<BR> Image is unknown <BR>'; 
                break; 

            case 1: 
                echo '<BR> Image is a GIF <BR>'; 
                $dest = $uploadpath.uniqid('img').'.gif'; 
                break; 
             
            case 2: 
                echo '<BR> Image is a JPG <BR>'; 
                $dest = $uploadpath.$origninal_name.'.jpg'; 
                break; 
             
            case 3: 
                echo '<BR> Image is a PNG <BR>'; 
                $dest = $uploadpath.uniqid('img').'.png'; 
                break; 

        } 


        if ( $dest != '' ) { 

            if ( move_uploaded_file( $source, $dest ) ) { 

                echo 'File successfully stored.<BR>'; 

            } else { 

                echo 'File could not be stored.<BR>'; 

            } 

        }  

    } else { 

        echo 'File not supplied, or file too big.<BR>'; 

    } 

?> 
