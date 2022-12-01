<?php
require('database.php');
$query = 'SELECT *
          FROM categories
          ORDER BY categoryID';
$statement = $db->prepare($query);
$statement->execute();
$categories = $statement->fetchAll();
$statement->closeCursor();

$product_id = filter_input(INPUT_POST, 'product_id', FILTER_VALIDATE_INT);
$product_code = filter_input(INPUT_POST, 'product_code', FILTER_VALIDATE_INT);
$product_name = filter_input(INPUT_POST, 'product_name');
$category_id = filter_input(INPUT_POST, 'category_id', FILTER_VALIDATE_INT);

?>
<!DOCTYPE html>
<html>

<!-- the head section -->
<head>
    <title>My Guitar Shop</title>
    <link rel="stylesheet" type="text/css" href="main.css">
</head>

<!-- the body section -->
<body>
    <header><h1>Product Manager</h1></header>

    <main>
        <h1>Update Product</h1>
        <form action="update_product.php" method="post"
              id="update_product_form">

            <label>Category:</label>
            <select name="category_id">
            <?php foreach ($categories as $category) : ?>
                <option value="<?php echo $category['categoryID']; ?>">
                    <?php echo $category['categoryName']; ?>
                </option>
            <?php endforeach; ?>
            </select><br>

            <label>Code:</label>
            <input type="text" name="code" value=<?php echo $product_code ?>><br>

            <label>Name:</label>
            <input type="text" name="name" value=<?php echo $product_name ?> ><br>

            <label>List Price:</label>
            <input type="text" name="price"><br>

            <label>&nbsp;</label>
            <input type="submit" value="Update"><br>
        </form>
        <p><a href="index.php">View Product List</a></p>
    </main>

    <footer>
        <p>&copy; <?php echo date("Y"); ?> My Guitar Shop, Inc.</p>
    </footer>
</body>
</html>
