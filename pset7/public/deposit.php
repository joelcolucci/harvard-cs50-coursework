<?php
    // configuration
    require("../includes/config.php"); 
    
    $id = $_SESSION["id"];

    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        $post_deposit = $_POST["deposit"];
        
        if (empty($post_deposit))
        {
            apologize("Please enter a value amount you would like to deposit");
        }
        if ($post_deposit < 0 || $post_deposit > 10000)
        {
            apologize("Invalid deposit amount. Max: 10000 Min: 0");
        }
        
        $update_cash = query("UPDATE users SET cash = cash + ? WHERE id = ?", $post_deposit, $id);
        if ($update_cash === false)
        {
            apologize("Transaction failed!");
        }
        
        // log to transaction table
        $log_transaction = query("INSERT INTO transactions (user_id, type, symbol, shares, price)
            VALUES (?, ?, ?, ?, ?)", $id, "Deposit", "NA", "NA", $post_deposit);
        if ($log_transaction === false)
        {
            apologize("Failed to log transaction");
        }
        
        redirect("/");
    }
    else
    {
        render("deposit_form.php", ["title" => "Deposit"]);
    }

?>
