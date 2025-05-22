import LoginScene from './scenes/LoginScene.js';
import GameScene from './scenes/GameScene.js'; // Three.js

const config = {
  type: Phaser.AUTO,
  width: 1024,
  height: 600,
  scene: [LoginScene],
  parent: 'game-container'
};

const phaserGame = new Phaser.Game(config);

// Interfață globală pentru tranziție
window.start3DGame = function(user1, user2) {
  phaserGame.destroy(true); // oprim Phaser
  const container = document.getElementById('game-container');
  const game = new GameScene(container, user1, user2);
  game.init();
};
