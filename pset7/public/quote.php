<?php
    
    require("../includes/config.php");
    
    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // lookup stock symbol
        $stock = lookup($_POST["symbol"]);
        
        // check that symbole was found
        if ($stock === false)
        {
            apologize("Sorry, no symbol found");
        }
        else
        {
            $_SESSION["stock"] = $stock;
            render("/quote.php");
        }
    }
    else
    {
        // else render form
        render("quote_form.php");
    }

    
    
?>
