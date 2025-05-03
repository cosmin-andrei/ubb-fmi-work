import LoginScene from './scenes/LoginScene.js';
import GameScene from './scenes/GameScene.js';

const config = {
  type: Phaser.AUTO,
  width: 1024,
  height: 600,
  backgroundColor: '#1d1d1d',
  physics: {
    default: 'arcade',
    arcade: {
      gravity: { y: 0 },
      debug: false
    }
  },
  scene: [LoginScene, GameScene]
};

new Phaser.Game(config);
