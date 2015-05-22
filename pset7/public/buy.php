<?php
    
    // configuration
    require("../includes/config.php"); 
        
    // assign variable to super global
    $id = $_SESSION["id"];

    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        $post_symbol = strtoupper($_POST["symbol"]);
        $post_shares = $_POST["shares"];
        
        if (empty($post_symbol))
        {
            apologize("Please specify a stock to purchase.");
        }
        
        $is_valid = preg_match("/^\d+$/", $post_shares);
        
        if (empty($post_shares) || $is_valid == false)
        {
            apologize("Invalid number of shares.");
        } 
        
        // symbol check if in existence
        $stock_price = lookup($post_symbol);
        
        if ($stock_price == false)
        {
            apologize("Stock could not be found.");
        }
        else
        {
            $stock_price = $stock_price["price"];
        }
        
        // calculate purchase price
        $purchase_price = $stock_price * $_POST["shares"];
        
        // fetch how much cash user has
        $cash_avail = query("SELECT cash FROM users WHERE id = ?", $id);
        if ($cash_avail === false)
        {
            apologize("Transaction failed!");
        }
        $cash_avail = $cash_avail[0]["cash"];
  
        // verify validity of purchase
        if ($purchase_price > $cash_avail)
        {
            apologize("Not enough funds to complete transaction");
        }
        
        // purchase stock and update table
        $make_purchase = query("INSERT INTO portfolio (id, symbol, shares) VALUES (?, ?, ?) ON DUPLICATE KEY
            UPDATE shares = shares + VALUES(shares)", $id, $post_symbol, $post_shares);
        if ($make_purchase === false)
        {
            apologize("Transaction failed!");
        }
        
        // update cash
        $update_cash = query("UPDATE users SET cash = cash - ? WHERE id = ?", $purchase_price, $id);
        if ($update_cash === false)
        {
            apologize("Transaction failed!");
        }
        
        // log to transaction table
        $log_transaction = query("INSERT INTO transactions (user_id, type, symbol, shares, price)
            VALUES (?, ?, ?, ?, ?)", $id, "Buy", $post_symbol, $post_shares, $stock_price);
        if ($log_transaction === false)
        {
            apologize("Failed to log transaction");
        }
        
        
        // bring user back to portfolio
        redirect("/");
    }
    else
    {
        render("buy_form.php", ["title" => "Buy"]);
    }



?>
