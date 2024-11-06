document.addEventListener('DOMContentLoaded', () => {
    const table = document.getElementById('x-0');
    let player = Math.random() < 0.5 ? 'X' : 'O';
    let currentPlayer = player === 'X' ? 'X' : 'O';

    table.addEventListener('click', function(event) {
        const target = event.target;
        if (target.tagName === 'TD' && target.classList.contains('empty')) {
            target.textContent = currentPlayer;
            target.classList.remove('empty');
            checkGameOver();
            currentPlayer = currentPlayer === 'X' ? 'O' : 'X';
            if (currentPlayer !== player) {
                setTimeout(computerMove, 500);
            }
        }
    });

    function computerMove() {
        fetch('game.php', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify(getBoardState())
        })
            .then(response => response.json())
            .then(data => {
                const cell = table.querySelector(`td[data-row="${data.row}"][data-col="${data.col}"]`);
                cell.textContent = currentPlayer;
                cell.classList.remove('empty');
                if (data.gameOver) {
                    alert(data.gameOver === 'tie' ? "It's a tie!" : `${data.gameOver} wins!`);
                    resetGame();
                } else {
                    currentPlayer = currentPlayer === 'X' ? 'O' : 'X';
                }
            });
    }

    function getBoardState() {
        const state = [];
        for (let row = 0; row < 3; row++) {
            const rowState = [];
            for (let col = 0; col < 3; col++) {
                const cell = table.querySelector(`td[data-row="${row}"][data-col="${col}"]`);
                rowState.push(cell.textContent || '');
            }
            state.push(rowState);
        }
        return { board: state, player: currentPlayer };
    }

    function checkGameOver() {
        const board = getBoardState().board;
        const winner = getWinner(board);

        if (winner) {
            alert(`${winner} wins!`);
            resetGame();
        } else if (isBoardFull(board)) {
            alert("It's a tie!");
            resetGame();
        }
    }

    function getWinner(board) {

        for (let row = 0; row < 3; row++) {
            if (board[row][0] && board[row][0] === board[row][1] && board[row][1] === board[row][2]) {
                return board[row][0];
            }
        }

        for (let col = 0; col < 3; col++) {
            if (board[0][col] && board[0][col] === board[1][col] && board[1][col] === board[2][col]) {
                return board[0][col];
            }
        }

        if (board[0][0] && board[0][0] === board[1][1] && board[1][1] === board[2][2]) {
            return board[0][0];
        }
        if (board[0][2] && board[0][2] === board[1][1] && board[1][1] === board[2][0]) {
            return board[0][2];
        }
        return null;
    }

    function isBoardFull(board) {
        for (let row = 0; row < 3; row++) {
            for (let col = 0; col < 3; col++) {
                if (!board[row][col]) {
                    return false;
                }
            }
        }
        return true;
    }

    function resetGame() {
        const cells = table.getElementsByTagName('td');
        for (let cell of cells) {
            cell.textContent = '';
            cell.classList.add('empty');
        }
        player = Math.random() < 0.5 ? 'X' : 'O';
        currentPlayer = player === 'X' ? 'X' : 'O';
    }
});
