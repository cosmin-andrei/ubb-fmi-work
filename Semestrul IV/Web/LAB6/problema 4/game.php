<?php
header('Content-Type: application/json');

$data = json_decode(file_get_contents('php://input'), true);
$board = $data['board'];
$player = $data['player'];

function getComputerMove($board) {
    for ($row = 0; $row < 3; $row++) {
        for ($col = 0; $col < 3; $col++) {
            if ($board[$row][$col] === '') {
                return ['row' => $row, 'col' => $col];
            }
        }
    }
    return null;
}

function checkWin($board, $player) {

    for ($row = 0; $row < 3; $row++) {
        if ($board[$row][0] === $player && $board[$row][1] === $player && $board[$row][2] === $player) {
            return true;
        }
    }

    for ($col = 0; $col < 3; $col++) {
        if ($board[0][$col] === $player && $board[1][$col] === $player && $board[2][$col] === $player) {
            return true;
        }
    }

    if ($board[0][0] === $player && $board[1][1] === $player && $board[2][2] === $player) {
        return true;
    }
    if ($board[0][2] === $player && $board[1][1] === $player && $board[2][0] === $player) {
        return true;
    }
    return false;
}

function isBoardFull($board) {
    for ($row = 0; $row < 3; $row++) {
        for ($col = 0; $col < 3; $col++) {
            if ($board[$row][$col] === '') {
                return false;
            }
        }
    }
    return true;
}

$move = getComputerMove($board);
$board[$move['row']][$move['col']] = $player;

$gameOver = checkWin($board, $player) ? $player : (isBoardFull($board) ? 'tie' : null);

$response = [
    'row' => $move['row'],
    'col' => $move['col'],
    'gameOver' => $gameOver
];

echo json_encode($response);

