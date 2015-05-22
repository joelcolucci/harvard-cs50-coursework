<?php

    // configuration
    require("../includes/config.php"); 
    
    // get user id from session
    $id = $_SESSION["id"];
    
    // fetch all user stocks from database
    $rows = query("SELECT id, symbol, shares FROM portfolio WHERE id = $id");
    
    $positions = [];
    foreach ($rows as $row)
    {
        $stock = lookup($row["symbol"]);
        
        if ($stock !== false)
        {
            $value = number_format(($stock["price"] * $row["shares"]), $decimal = 2);
            $positions[] = [
            "name" => $stock["name"],
            "price" => number_format($stock["price"], $decimal = 2),
            "shares" => $row["shares"],
            "symbol" => $row["symbol"],
            "value" => $value
            ];
        }
    }
    
    // fetch users cash balance from the user table
    $cash = query("SELECT cash FROM users WHERE id = $id");
    $cash = number_format($cash[0]["cash"], $decimal = 2);
    
    // render portfolio
    render("portfolio.php", ["positions" => $positions, "cash" => $cash, "title" => "Portfolio"]);

?>
