<?php
$cartID = 1;
// Get the product id
$productID = filter_input(INPUT_POST, 'productID', FILTER_VALIDATE_INT);
    // Add the product to the car 
    $query = 'INSERT INTO cart
                 (cartID, productID)
              VALUES
                 (:cartID, :productID)';
    $statement = $db->prepare($query);
    $statement->bindValue(':cartID', $cartID);
    $statement->bindValue(':productID', $productID);
    $statement->execute();
    $statement->closeCursor();

    //Take you back to the shop
    include('shop.php');
}
?>
