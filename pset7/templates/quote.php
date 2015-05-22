<?php

    $stock = $_SESSION["stock"];
    
    // format price
    $price = number_format($stock["price"], $decimals = 2);
    
    // display stock details
    print("Price: $" . $price . " (" . $stock["symbol"] . ")   -" .
       "   Company: " . $stock["name"]);

?>
