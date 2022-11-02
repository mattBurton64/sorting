<?php
require_once('database.php');

// Get category ID
if (!isset($category_id)) {
    $category_id = filter_input(INPUT_GET, 'category_id', 
            FILTER_VALIDATE_INT);
    if ($category_id == NULL || $category_id == FALSE) {
        $category_id = 1;
    }
}

// Get name for selected category
$queryCategory = 'SELECT * FROM categories
                  WHERE categoryID = :category_id';
$statement1 = $db->prepare($queryCategory);
$statement1->bindValue(':category_id', $category_id);
$statement1->execute();
$category = $statement1->fetch();
$category_name = $category['categoryName'];
$statement1->closeCursor();


// Get all categories
$query = 'SELECT * FROM categories
                       ORDER BY categoryID';
$statement = $db->prepare($query);
$statement->execute();
$categories = $statement->fetchAll();
$statement->closeCursor();

// Get products for selected category
$queryProducts = 'SELECT * FROM products
                  WHERE categoryID = :category_id
                  ORDER BY productID';
$statement3 = $db->prepare($queryProducts);
$statement3->bindValue(':category_id', $category_id);
$statement3->execute();
$products = $statement3->fetchAll();
$statement3->closeCursor();
?>
<!DOCTYPE html>
<html>
  <head>
    <title>Title Text</title>
    <link rel="stylesheet" href="style.css">
    <!--<link rel="icon" href="Images/favicon.png" type="image/png">-->
    <style type=text/css>
    input#image-button{
      background: #ccc url('soccer.jpg') no-repeat top left;
      padding-left: 16px;
      height: 16px;
    }
    .line {
      border-color: #fcce58;
    }
    .products {
      margin: 1vw auto 2vw auto;
    }
    .products td {
      padding: 1vw 2vw;
    }
    .products th {
      padding: 1vw 2vw;
    }
    .products tr {
      background-color: #eeeeee;
    }
    </style>
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
  </head>

  <body>
    <nav class=line>
      <ul>
        <li><a href="index.html">HOME</a></li>      
        <li><a href="shop.php">SHOP</a></li>
        <li><a href="checkout.php">CHECKOUT</a></li> 
        <li style="float:right;padding: 0 3vw 0 0;"><a href="sign-in.php">SIGN IN</a></li>
        <li style=float:right><a href="register.php">REGISTER</a></li>
      </ul>
    </nav> 
    
    <h1 class=center>Sports</h1>
    <table>
      <tr>
        <td><a href="shop.php?category_id=1#products"><img class=sports src="images/basketball.jpg" alt="basketball"></a></td>
        <td><a href="shop.php?category_id=2#products"><img class=sports src="images/baseball.jpg" alt="baseball"></a></td>
        <td><a href="shop.php?category_id=3#products"><img class=sports src="images/lacrosse.jpg" alt="lacrosse"></a></td>
      </tr>
        <td><a href="shop.php?category_id=4#products"><img class=sports src="images/football.jpg" alt="football"></a></td>
        <td><a href="shop.php?category_id=5#products"><img class=sports src="images/soccer.jpg" alt="soccer"></a></td>
        <td><a href="shop.php?category_id=6#products"><img class=sports src="images/hockey.jpg" alt="hockey"></a></td>
      </tr>
    </table>

    <h2 id=products><?php echo $category['categoryName'] ?></h2>
       
    <div class=products>
      <table>
         <tr>
            <th>Name</th>
            <th class="right">Price</th>
            <th>Add to Cart</th>
         </tr>

         <?php foreach ($products as $product) : ?>
         <tr>
            <td><?php echo $product['productName']; ?></td>
            <td class="right"><?php echo $product['listPrice']; ?></td>
            <td><form action="add-to-cart.php" method="post">
               <input type=hidden name=productID value="<?php echo $product['productID']; ?>">
               <input type="submit" value="Add">
            </form></td>
         </tr>
         <?php endforeach; ?>
      </table>
   </div>
   
    <nav class=line> 
      <ul>
        <li><a href="index.html">HOME</a></li>      
        <li><a href="shop.php">SHOP</a></li>
        <li><a href="checkout.php">CHECKOUT</a></li>
        <li style="float:right;padding: 0 3vw 0 0;"><a href="sign-in.php">SIGN IN</a></li>
        <li style=float:right><a href="register.php">REGISTER</a></li>
      </ul>
    </nav> 
    <footer>
      <p>Copyright &copy; <script>document.write(new Date().getFullYear())</script> Matthew Burton</p>
    </footer>  
  </body>

</html>
