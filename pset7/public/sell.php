<?php

    // configuration
    require("../includes/config.php"); 
    
    $id = $_SESSION["id"];
    
    // get array of stock symbols owned by user
    $stocks = query("SELECT symbol FROM portfolio WHERE id = ?", $id);
    if ($stocks === false)
    {
        apologize("Whoops! You currently do not own any stocks");
    }
      
    // on submit
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        $post_symbol = $_POST["symbol"];
        
        // ensure all fields were completed
        if (empty($post_symbol))
        {
            apologize("Woops! You forgot to select a stock.");
        }
        
        $shares = query("SELECT * FROM portfolio WHERE id = $id AND symbol = ?", $post_symbol);
        if ($shares === false)
        {
            apologize("Error Sale Ended: Could not access database");
        }
        
        // calculate value of sold stocks
        $num_shares = $shares[0]["shares"];
        $stock_price = lookup($post_symbol);
        $sale_value = $stock_price["price"] * $num_shares;

        
        // update users table with new cash info
        $did_update = query("UPDATE users SET cash = cash + ? WHERE id = ?", $sale_value, $id);
        if ($did_update === false)
        {
            apologize("Error Sale Ended: Unable to process your sale!");
        }
        
        // delete record from portfolio
        $did_delete = query("DELETE FROM portfolio WHERE id = ? AND symbol = ?", $id, $post_symbol);
        if ($did_delete === false)
        {
            apologize("Error: Unable to update portfolio");
        }
        
        // log to transaction table
        $log_transaction = query("INSERT INTO transactions (user_id, type, symbol, shares, price)
            VALUES (?, ?, ?, ?, ?)", $id, "Sell", $post_symbol, $num_shares, $sale_value);
        if ($log_transaction === false)
        {
            apologize("Failed to log transaction");
        }
        
        redirect("/");
    }
    else
    {
        // pass info to sell_form.php
        render("sell_form.php", ["title" => "Sell", "stocks" => $stocks]);
    }
?>
