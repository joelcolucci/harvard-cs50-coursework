<table class="table table-striped">
    <thead>
        <tr>
            <td>Transaction Type</td>
            <td>Date/Time</td>
            <td>Stock Symbol</td>
            <td>Amount of Shares</td>
            <td>Amount</td>
        </tr>
    </thead>
    
    <tbody>
        <?php foreach ($transactions as $transaction) : ?>
            <tr>
                <td><?= $transaction["type"] ?></td>
                <td><?= $transaction["timestamp"] ?></td>
                <td><?= $transaction["symbol"] ?></td>
                <td><?= $transaction["shares"] ?></td>
                <td>$<?= $transaction["price"] ?></td>
            </tr>
        <?php endforeach ?>
    </tbody>
</table>
