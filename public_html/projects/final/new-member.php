<?php
// Get the product data
$first = filter_input(INPUT_POST, 'first');
$middle = filter_input(INPUT_POST, 'middle');
$last = filter_input(INPUT_POST, 'last');
$email = filter_input(INPUT_POST, 'email');
$password = filter_input(INPUT_POST, 'password');
$gender = filter_input(INPUT_POST, 'gender');

// Validate inputs
if ($first == null || $middle == null || $last == null || $email == null || $password == null || $gender == null) {
    $error = "Invalid product data. Check all fields and try again.";
} else {
    require_once('database.php');

    // Add the product to the database  
    $query = 'INSERT INTO members
                 (id, first, middle, last, email, password, gender)
              VALUES
                 (:id, :first, :middle, :last, :email, :password, :gender)';
    $statement = $db->prepare($query);
    $statement->bindValue(':id', NULL);
    $statement->bindValue(':first', $first);
    $statement->bindValue(':middle', $middle);
    $statement->bindValue(':last', $last);
    $statement->bindValue(':email', $email);
    $statement->bindValue(':password', $password);
    $statement->bindValue(':gender', $gender);
    $statement->execute();
    $statement->closeCursor();

    //Takes you to the shop
    include('shop.php');
}
?>
