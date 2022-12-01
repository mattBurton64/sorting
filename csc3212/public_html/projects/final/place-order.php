<?php
// Get the product id
$cartID = filter_input(INPUT_POST, 'cartID', FILTER_VALIDATE_INT);
$email = filter_input(INPUT_POST, 'email', FILTER_VALIDATE_INT);
    // Add the product to the car 
    $query = 'INSERT INTO orders
                 (cartID, email)
              VALUES
                 (:cartID, :email)';
    $statement = $db->prepare($query);
    $statement->bindValue(':cartID', $cartID);
    $statement->bindValue(':email', $email);
    $statement->execute();
    $statement->closeCursor();

    //Take you back to the shop
    include('shop.php');
}
?>
