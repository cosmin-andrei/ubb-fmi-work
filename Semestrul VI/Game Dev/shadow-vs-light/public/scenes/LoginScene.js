export default class LoginScene extends Phaser.Scene {
    constructor() {
        super('LoginScene');
        this.activeField = null;
        this.usernames = {
            user1: '',
            user2: ''
        };
    }

    create() {
        this.cameras.main.setBackgroundColor('#f0f0f0');

        const gradient = this.add.graphics();
        gradient.fillGradientStyle(0xffc3a0, 0xffc3a0, 0x8ec5fc, 0x8ec5fc, 1);
        gradient.fillRect(0, 0, 1024, 600);
        gradient.setDepth(-1);

        this.add.text(512, 80, 'Introduceți numele jucătorilor', {
            fontSize: '28px',
            fill: '#000',
            fontFamily: 'Arial'
        }).setOrigin(0.5);


        this.user1Field = this.createInputField(512, 200, 'Jucător stânga', 'user1');
        this.user2Field = this.createInputField(512, 270, 'Jucător dreapta', 'user2');


        const startButton = this.add.text(512, 370, 'Start Game', {
            fontSize: '28px',
            fill: '#fff',
            backgroundColor: '#28a745',
            padding: { x: 20, y: 10 },
            borderRadius: 8
        }).setOrigin(0.5).setInteractive({ useHandCursor: true });

        startButton.on('pointerdown', () => {
            if (this.usernames.user1.trim() === '' || this.usernames.user2.trim() === '') {
                this.showError('Completați ambele nume!');
                return;
            }

            this.scene.start('GameScene', {
                user1: this.usernames.user1,
                user2: this.usernames.user2
            });
        });


        this.input.keyboard.on('keydown', (event) => {
            if (!this.activeField) return;

            const key = event.key;

            if (key === 'Backspace') {
                this.usernames[this.activeField] = this.usernames[this.activeField].slice(0, -1);
            } else if (key.length === 1 && this.usernames[this.activeField].length < 12) {
                this.usernames[this.activeField] += key;
            }

            this.updateInputText(this.activeField);
        });
    }

    createInputField(x, y, placeholder, key) {
        const box = this.add.rectangle(x, y, 320, 50, 0xffffff).setStrokeStyle(2, 0x000000).setInteractive();
        const text = this.add.text(x, y, placeholder, {
            fontSize: '20px',
            fill: '#000',
            fontFamily: 'Arial'
        }).setOrigin(0.5);

        box.on('pointerdown', () => {
            this.activeField = key;
            this.updateInputText(key);
        });

        return { box, text, key };
    }

    updateInputText(key) {
        const input = key === 'user1' ? this.user1Field : this.user2Field;
        const value = this.usernames[key];
        input.text.setText(value || (key === 'user1' ? 'Jucător stânga' : 'Jucător dreapta'));
    }

    showError(msg) {
        const error = this.add.text(512, 440, msg, {
            fontSize: '18px',
            fill: '#ff0000',
            fontFamily: 'Arial'
        }).setOrigin(0.5);

        this.time.delayedCall(2000, () => error.destroy());
    }
}
