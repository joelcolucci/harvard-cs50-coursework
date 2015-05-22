<ul class="nav nav-pills">
    <li><a href="deposit.php">Deposit Funds</a></li>
    <li><a href="quote.php">Quote</a></li>
    <li><a href="buy.php">Buy</a></li>
    <li><a href="sell.php">Sell</a></li>
    <li><a href="history.php">History</a></li>
    <li><a href="logout.php"><strong>Log Out</strong></a></li>
</ul>
  
<table class="table table-striped">

    <thead>
        <tr>
            <th>Symbol</th>
            <th>Name</th>
            <th>Shares</th>
            <th>Price</th>
            <th>TOTAL</th>
        </tr>
    </thead>

    <tbody>
        <?php foreach ($positions as $holding): ?>
            <tr>
                <td> <?= $holding["symbol"] ?> </td>
                <td> <?= $holding["name"] ?> </td>
                <td> <?= $holding["shares"] ?> </td>
                <td> $<?= $holding["price"] ?> </td>
                <td> $<?= $holding["value"] ?> </td>
            </tr>
        <?php endforeach ?>

        <tr>
            <td colspan="4">CASH</td>
        <?php if (isset($cash)): ?>
            <td> $<?= $cash ?> </td>
        <?php else: ?>
            <td> Not available </td>
        <?php endif ?>
        </tr>
    </tbody>
</table>
