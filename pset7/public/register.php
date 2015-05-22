<?php

    // configuration
    require("../includes/config.php");
    
    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // ensure all fields were completed
        if (empty($_POST["username"]))
        {
            apologize("Woops! You forgot to enter a username.");
        }
        else if (empty($_POST["password"]))
        {
            apologize("Woops! You forgot to enter a password.");
        }
        else if ($_POST["password"] !== $_POST["confirmation"])
        {
            apologize("Woops! Your passwords do not match.");
        }
        
        // insert the new user into the database
        $did_insert = query("INSERT INTO users (username, hash, cash) VALUES (?, ?, 10000.00)", $_POST["username"],crypt($_POST["password"]));
        
        if ($did_insert === false)
        {
            apologize("You already have an account with C$50 Finance. Please log in instead.");
        }
        
        // INSERT has succeeded, carry on
        $rows = query("SELECT LAST_INSERT_ID() AS id");
        $id = $rows[0]["id"];
        
        // remember the id via session
        $_SESSION["id"] = $id;
        
        redirect("/index.php");
    }
    else
    {
        // else render form
        render("register_form.php", ["title" => "Register"]);
    }
 
?>
