export default class GameScene extends Phaser.Scene {
  constructor() {
    super('GameScene');
    this.FIXED_SCALE = 1.5;
    this.STAND_SCALE = 1.5;
    this.PUNCH_SCALE = 1.5;
  }

  init(data) {
    this.user1 = data.user1 || 'Jucător A';
    this.user2 = data.user2 || 'Jucător L';

    // Score
    this.score = { A: 0, B: 0 };
    this.rounds = { A: 0, B: 0 };

    this.attackCooldown = 500; // timp minim intre atacuri
    this.lastAttack = { A: 0, B: 0 };
    this.roundOngoing = true;
  }

  preload() {
    this.load.image('ring', 'assets/ring.png');
    this.load.image('leftStand', 'sprites/leftStand.png');
    this.load.image('rightStand', 'sprites/rightStand.png');
    this.load.image('leftPunch', 'sprites/leftPunch.png');
    this.load.image('rightPunch', 'sprites/rightPunch.png');
  }

  create() {
    this.add.image(0, 0, 'ring').setOrigin(0).setDisplaySize(1024, 600);

    // Container A
    this.containerA = this.add.container(200, 450);
    // Sprite A
    this.playerA = this.physics.add.sprite(0, 0, 'leftStand')
        .setScale(this.STAND_SCALE)
        .setOrigin(0.5)
        .setFlipX(true); // orientat spre dreapta
    this.containerA.add(this.playerA);

    // Container B (dreapta)
    this.containerB = this.add.container(800, 450);
    // Sprite B
    this.playerB = this.physics.add.sprite(0, 0, 'rightStand')
        .setScale(this.STAND_SCALE)
        .setOrigin(0.5)
        .setFlipX(true);
    this.containerB.add(this.playerB);


    this.physics.world.enable([this.containerA, this.containerB]);

    //gravitatie 0
    this.containerA.body.allowGravity = false;
    this.containerB.body.allowGravity = false;

    this.containerA.body.setCollideWorldBounds(true);
    this.containerB.body.setCollideWorldBounds(true);

    this.controls = this.input.keyboard.addKeys({
      A_LEFT: 'A',
      A_RIGHT: 'D',
      A_ATTACK: 'S',
      B_LEFT: 'LEFT',
      B_RIGHT: 'RIGHT',
      B_ATTACK: 'DOWN'
    });

    // Score text
    this.scoreTextA = this.add.text(50, 40, `${this.user1}: 0`, {
      fontSize: '24px',
      fill: '#000'
    });
    this.scoreTextB = this.add.text(924, 40, `${this.user2}: 0`, {
      fontSize: '24px',
      fill: '#000'
    }).setOrigin(1, 0);


    this.roundText = this.add.text(512, 20, 'Runda 1', {
      fontSize: '28px',
      fill: '#fff'
    }).setOrigin(0.5);

    // Bare de viata
    this.healthBarA = this.add.graphics();
    this.healthBarB = this.add.graphics();
    this.drawHealthBar('A', 0);
    this.drawHealthBar('B', 0);
  }

  update(time) {
    if (!this.roundOngoing) return;

    // Miscare A (container)
    if (this.controls.A_LEFT.isDown) {
      this.containerA.x -= 3;
    } else if (this.controls.A_RIGHT.isDown) {
      this.containerA.x += 3;
    }

    // miscare cointainer
    if (this.controls.B_LEFT.isDown) {
      this.containerB.x -= 3;
    } else if (this.controls.B_RIGHT.isDown) {
      this.containerB.x += 3;
    }

    // Atac A
    if (
        Phaser.Input.Keyboard.JustDown(this.controls.A_ATTACK) &&
        time - this.lastAttack.A > this.attackCooldown
    ) {

      const flip = this.playerA.flipX;
      this.playerA.setTexture('leftPunch');
      this.playerA.setScale(this.PUNCH_SCALE);
      this.playerA.setFlipX(flip);

      this.time.delayedCall(200, () => {
        this.playerA.setTexture('leftStand');
        this.playerA.setScale(this.STAND_SCALE);
        this.playerA.setFlipX(flip);
      });
      this.lastAttack.A = time;

      // se intersectează  => B
      if (Phaser.Geom.Intersects.RectangleToRectangle(
          this.containerA.getBounds(),
          this.containerB.getBounds()
      ))
      {
        this.score.B++;
        this.updateScore();
        this.damagePlayer(this.containerB, 'B');
      }
    }

    // Atac B
    if (
        Phaser.Input.Keyboard.JustDown(this.controls.B_ATTACK) &&
        time - this.lastAttack.B > this.attackCooldown
    ) {
      const flip = this.playerB.flipX;
      this.playerB.setTexture('rightPunch');
      this.playerB.setScale(this.PUNCH_SCALE);
      this.playerB.setFlipX(flip);

      this.time.delayedCall(200, () => {
        this.playerB.setTexture('rightStand');
        this.playerB.setScale(this.STAND_SCALE);
        this.playerB.setFlipX(flip);
      });
      this.lastAttack.B = time;

      // A lovitura
      if (Phaser.Geom.Intersects.RectangleToRectangle(
          this.containerB.getBounds(),
          this.containerA.getBounds()
      ))
      {
        this.score.A++;
        this.updateScore();
        this.damagePlayer(this.containerA, 'A');
      }
    }
  }

  damagePlayer(targetContainer, key) {
 //shake
    this.cameras.main.shake(100, 0.01);
    this.tweens.add({
      targets: targetContainer,
      x: targetContainer.x + (key === 'A' ? -10 : 10),
      duration: 100,
      yoyo: true
    });

    // life bar
    this.updateHealthBar(key);

    // 5 lovituri => runda pierduta
    if (this.score[key] >= 5) {
      this.roundOngoing = false;
      const winner = (key === 'A') ? 'B' : 'A';
      this.rounds[winner]++;

      this.roundText.setText(
          `Runda câștigată de ${winner === 'A' ? this.user1 : this.user2}`
      );

      if (this.rounds[winner] === 3) {
        // Final
        this.endMatch(winner);
      } else {
        // new round
        this.time.delayedCall(2000, () => this.startNextRound());
      }
    }
  }

  drawHealthBar(key, hits) {
    // hits = this.score[key]
    const bar = key === 'A' ? this.healthBarA : this.healthBarB;
    bar.clear();
    const x = key === 'A' ? 50 : 774;
    const color = key === 'A' ? 0xff4444 : 0x4444ff;

    bar.fillStyle(0x000000);
    bar.fillRect(x - 2, 70 - 2, 204, 24);

    const maxWidth = 200;
    const hitsRatio = hits / 5;
    const barWidth = maxWidth * (1 - hitsRatio);

    bar.fillStyle(color);
    bar.fillRect(x, 70, barWidth, 20);
  }

  updateHealthBar(key) {
    this.drawHealthBar(key, this.score[key]);
  }

  updateScore() {
    this.scoreTextA.setText(`${this.user1}: ${this.score.A}`);
    this.scoreTextB.setText(`${this.user2}: ${this.score.B}`);
  }

  startNextRound() {
    this.roundOngoing = true;
    this.score = { A: 0, B: 0 };
    this.updateScore();

    this.drawHealthBar('A', 0);
    this.drawHealthBar('B', 0);

    this.roundText.setText(`Runda ${this.rounds.A + this.rounds.B + 1}`);

    //sprite
    const flipA = this.playerA.flipX;
    const flipB = this.playerB.flipX;

    this.playerA.setTexture('leftStand');
    this.playerA.setScale(this.STAND_SCALE);
    this.playerA.setFlipX(flipA);

    this.playerB.setTexture('rightStand');
    this.playerB.setScale(this.STAND_SCALE);
    this.playerB.setFlipX(flipB);

    this.containerA.x = 200;
    this.containerB.x = 800;
  }

  endMatch(winnerKey) {
    this.add.rectangle(512, 300, 1024, 600, 0x000000, 0.8);
    this.add.text(512, 300, `${winnerKey === 'A' ? this.user1 : this.user2} câștigă meciul!`, {
      fontSize: '36px',
      fill: '#fff'
    }).setOrigin(0.5);


    this.time.delayedCall(4000, () => this.scene.start('LoginScene'));
  }
}
