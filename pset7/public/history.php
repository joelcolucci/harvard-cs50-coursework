<?php
    // configuration
    require("../includes/config.php"); 
    
    // get user id from session
    $id = $_SESSION["id"];
    
    $transactions = query("SELECT * FROM transactions WHERE user_id = ? ORDER BY timestamp DESC", $id);
    if ($transactions === false)
    {
        apologize("No history available.");
    }
    
    // transfer query results into new associative array with formatted values
    $formatted_trans = [];
    foreach ($transactions as $trans)
    {
        $formatted_trans[] = [
        "type" => $trans["type"],
        "timestamp" => date('m/d/y h:m A', strtotime($trans["timestamp"])),
        "symbol" => $trans["symbol"],
        "shares" => $trans["shares"],
        "price" => number_format($trans["price"], $decimal = 2)
        ];
    }
     
    render("history.php", ["title" => "Transactions", "transactions" => $formatted_trans]);

?>
